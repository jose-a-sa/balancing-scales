# balancing-scales

## Building

This project uses CMake and a C++20 compiler. To build the project, run:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release -j8
```

This will produce the executable `balance-scales` in the `build/` directory.

## Running

The program reads CSV data from standard input. Example usage:

```sh
build/balance-scales < input.in
```

```sh
cat input.in | build/balance-scales
```

## Testing

Test cases are provided in the `tests/` directory as `.in` (input) and `.out` (expected output) file pairs.

To run all tests and compare outputs, you can use the following shell loop:

```sh
for t in tests/*.in; do
    base=$(basename "$t" .in);
    diff -w <(cat "tests/$base.out") <(build/balance-scales < "$t") && echo "$base: PASS" || echo "$base: FAIL";
done
```

Automated building and running of tests can be done via `build_and_run_tests.sh`
