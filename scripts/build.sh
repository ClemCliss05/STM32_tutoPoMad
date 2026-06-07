#!/bin/bash
set -e

BUILD_DIR=build
FIRMWARE_DIR=build/build_firmware
TESTS_DIR=$BUILD_DIR/build_tests

build() {
    cmake -B $FIRMWARE_DIR \
    -DCMAKE_TOOLCHAIN_FILE=cmake/arm-gcc-toolchain.cmake

    cmake --build $FIRMWARE_DIR
}

test() {
    cmake -B $TESTS_DIR -DANALYSIS=ON -DTESTS=ON
    cmake --build $TESTS_DIR
    ctest --test-dir $TESTS_DIR
}

flash() {
    JLinkExe \
    -device STM32F072RB \
    -if SWD \
    -speed 4000 \
    -autoconnect 1 \
    -CommanderScript scripts/flash_jlink.sh
}

clean() {
    rm -rf $BUILD_DIR
}

case "$1" in
    test)
        test
        ;;
    flash)
        build
        flash
        ;;
    clean)
        clean
        ;;
    *)
        build
        ;;
esac