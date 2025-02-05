#!/bin/bash

# Compile the source code
g++ ./code/main.cpp -o ./release/main -std=c++23 -lncurses

# Run the executable if there are no errors in compilation
if [ $? -eq 0 ]; then
    ./release/main
fi