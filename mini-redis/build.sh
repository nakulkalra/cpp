#!/bin/bash

set -e

BUILD_DIR="build"

mkdir -p $BUILD_DIR

cmake -B $BUILD_DIR
cmake --build $BUILD_DIR
