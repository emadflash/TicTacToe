#!/usr/bin/env bash

set -eu

TARGET_DIR="target"
BIN="tictactoe"

panic() {
    printf "%s\n" "$1"
    exit 1
}

create_directory() {
    if [[ ! -d ${TARGET_DIR} ]]; then
      mkdir ${TARGET_DIR} 2>/dev/null
    fi
}

build() {
    create_directory ${TARGET_DIR}

    case $1 in
    debug)
        create_directory "${TARGET_DIR}/debug"
        cmake -B "${TARGET_DIR}/debug" -DCMAKE_BUILD_TYPE=Debug
        make -C "${TARGET_DIR}/debug"
        ;;

    release)
        create_directory "${TARGET_DIR}/release"
        cmake -B "${TARGET_DIR}/release" -DCMAKE_BUILD_TYPE=Release
        make -C "${TARGET_DIR}/debug"
        ;;

    *)
        panic "Build mode unsupported!"
    esac
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
