#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <day> <test (true/false)>"
    exit 1
fi

day=$1
test=$2

directory="src/day$(printf "%02d" "$day")"
code_file="${directory}/main.cpp"
input_file="${directory}/input.txt"

if [ "$test" == "false" ]; then
    input_file="${directory}/test.txt"
fi

g++ -Wall -std=gnu++17 -O2 -o current "$code_file" -lm && \
./current < "$input_file" && \
rm -f ./current
