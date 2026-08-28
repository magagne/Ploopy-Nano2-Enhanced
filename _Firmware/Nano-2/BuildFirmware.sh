#!/bin/bash

set -euo pipefail

# Ploopy Nano 2 firmware builder
# Builds: ploopyco/nano_2/rev2_003:via_scrolllock
#
# The script is self-contained and derives all paths from its own location.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

QMK_DIR="$REPO_DIR"
FIRMWARE_DIR="$SCRIPT_DIR"

FIRMWARE_NAME="ploopyco_nano_2_rev2_003_via_scrolllock.uf2"
FIRMWARE_SOURCE="$QMK_DIR/.build/$FIRMWARE_NAME"
ROOT_FIRMWARE="$QMK_DIR/$FIRMWARE_NAME"

DOCKER_IMAGE="ghcr.io/qmk/qmk_cli"
BUILD_TARGET="ploopyco/nano_2/rev2_003:via_scrolllock"

printf '\n=== PLOOPY NANO 2 FIRMWARE BUILD ===\n\n'

if ! command -v docker >/dev/null 2>&1; then
    echo "ERROR: Docker command not found."
    echo "Please install Docker Desktop first."
    exit 1
fi

if ! docker info >/dev/null 2>&1; then
    echo "→ Starting Docker Desktop..."
    open -a Docker

    echo "→ Waiting for Docker to become ready..."

    for _ in {1..60}; do
        if docker info >/dev/null 2>&1; then
            break
        fi
        sleep 2
    done
fi

if ! docker info >/dev/null 2>&1; then
    echo
    echo "ERROR: Docker Desktop did not become ready within 120 seconds."
    exit 1
fi

echo "→ Docker is ready."
echo "→ Building $BUILD_TARGET..."
echo

rm -f "$FIRMWARE_SOURCE"
rm -f "$ROOT_FIRMWARE"
rm -f "$FIRMWARE_DIR/$FIRMWARE_NAME"

docker run --rm -i \
    --user "$(id -u):$(id -g)" \
    -w /qmk_firmware \
    -v "$QMK_DIR:/qmk_firmware" \
    -e SKIP_GIT=1 \
    "$DOCKER_IMAGE" \
    make "$BUILD_TARGET"

# QMK places a copy at the repository root.
# Remove it so only the organized firmware directory remains.
rm -f "$ROOT_FIRMWARE"

echo
echo "→ Checking firmware output..."

if [[ ! -f "$FIRMWARE_SOURCE" ]]; then
    echo
    echo "ERROR: Build completed but the expected firmware was not found:"
    echo "  $FIRMWARE_SOURCE"
    echo
    echo "Available UF2 files in .build:"
    find "$QMK_DIR/.build" -maxdepth 1 -type f -name '*.uf2' -print 2>/dev/null || true
    exit 1
fi

cp "$FIRMWARE_SOURCE" "$FIRMWARE_DIR/$FIRMWARE_NAME"

echo "→ Firmware copied to:"
echo "  $FIRMWARE_DIR/$FIRMWARE_NAME"

echo
echo "=== BUILD COMPLETE ==="
echo

ls -lh "$FIRMWARE_DIR/$FIRMWARE_NAME"
