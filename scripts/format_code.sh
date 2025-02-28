#!/bin/bash

# Get the absolute path of the script's directory
SCRIPT_DIR=$(dirname "$(realpath "$0")")

# Find all .cpp and .h files and format them using clang-format
find "$SCRIPT_DIR/.." -name '*.cpp' -o -name '*.h' | xargs clang-format -i