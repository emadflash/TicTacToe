#!/usr/bin/env bash

set -eu

: ${CC=clang++}
: ${CFLAGS=}
: ${LDFLAGS=}

TARGET_DIR="target"
BIN="tictactoe"
CFLAGS="$CFLAGS -std=c++17 -I./include -I./src/headers"
LDFLAGS="$LDFLAGS -lm ./lib/libSDL2.so"
SOURCES="src/*.cpp"

panic() {
    printf "%s\n" "$1"
    exit 1
}

create_target_dir() {
    if [[ ! -d $TARGET_DIR ]]; then
      mkdir $TARGET_DIR 2>/dev/null
    fi
}

build() {
    case $1 in
    debug)
        EXTRAFLAGS="-Wall -Wextra -pedantic -ggdb -DDebug"
        ;;

    release)
        EXTRAFLAGS="-O3 -DRelease"
        ;;

    *)
        panic "Build mode unsupported!"
    esac

    set -x
    create_target_dir
    $CC $CFLAGS $EXTRAFLAGS $LDFLAGS $SOURCES -o $TARGET_DIR/$BIN
    set +x
}

if [[ $# -eq 0 ]]; then
    build debug
    exit 0
fi

if [[ $# -eq 1 ]]; then
    build $1
    exit 0
else
    panic "Too many arguments"
fi
