#!/usr/bin/env bash

# configure
cmake -B build -DCMAKE_BUILD_TYPE=Release

# build
cmake --build build --config Release -j8

# run tests
ctest --test-dir build -C Release -T test --output-on-failure -j8


# for t in tests/*.in; do
#     name=$(basename "$t" .in);

#     in_file="tests/$name.in"
#     out_file="tests/$name.out"

#     [[ ! -f "$out_file" ]] && continue;

#     diff -w <(build/balance-scales < "$in_file") <(cat "$out_file")
#     [ $? -eq 0 ] && echo "$name: PASS" || echo "$name: FAIL"
# done
