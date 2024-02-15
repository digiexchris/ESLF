#!/bin/bash
echo "Running tests"
LLVM_PROFILE_FILE="build/test/elsf_tests.profraw" ./build/test/elsf_tests &&
echo "Merging coverage"
llvm-profdata merge -sparse build/test/default.profraw build/test/elsf_tests.profraw -o build/test/default.profdata &&
echo "Exporting lconv"
llvm-cov export -format=lcov build/test/elsf_tests -instr-profile=build/test/default.profdata > coverage/lcov.info 
#echo "Displaying coverage"
#llvm-cov show build/test/elsf_tests -instr-profile=build/test/default.profdata -show-line-counts-or-regions -Xdemangler c++filt


