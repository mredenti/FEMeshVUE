#!/bin/bash

# Get the absolute path of the script's directory
SCRIPT_DIR=$(dirname "$(realpath "$0")")

# Get the parent directory (assumes the script is in the "scripts" folder)
PARENT_DIR=$(realpath "$SCRIPT_DIR/..")

# Export the parent directory as the clang-format configuration directory
CLANG_FORMAT_STYLE="file:$PARENT_DIR/.clang-format"

# Find all .cpp and .h files and format them using clang-format
find "$PARENT_DIR" -name '*.cpp' -o -name '*.h' | xargs clang-format -i --style="$CLANG_FORMAT_STYLE"