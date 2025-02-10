# !/bin/bash
clear
# Compile the source code
g++ ./code/main.cpp -o ./release/main -std=c++23 -lncursesw -DNCURSES_WIDECHAR=1 -fexec-charset=UTF-8

# Run the executable if there are no errors in compilation
if [ $? -eq 0 ]; then
    ./release/main
fi
