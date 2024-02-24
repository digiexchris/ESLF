#!/bin/bash
IGNORELIST='.*include/Machine/MessageBus/(Router\.hpp|Subscription\.hpp)'
echo "Clearing lconv" &&
rm -R coverage/lcov.info coverage/elsf_tests.profdata coverage/elsf_tests.profraw coverage/html
echo "Running tests" &&
LLVM_PROFILE_FILE="coverage/elsf_tests.profraw" ./build/test/elsf_tests &&
echo "Merging coverage" &&
llvm-profdata merge coverage/elsf_tests.profraw -o coverage/elsf_tests.profdata &&

echo "Exporting lconv"
llvm-cov export -ignore-filename-regex=$IGNORELIST -format=lcov build/test/elsf_tests -instr-profile=coverage/elsf_tests.profdata > coverage/lcov.info 
echo "Generating html coverage"
llvm-cov show  build/test/elsf_tests -ignore-filename-regex=$IGNORELIST -instr-profile=coverage/elsf_tests.profdata -show-line-counts-or-regions -Xdemangler c++filt -format=html -output-dir=coverage/html -project-title="Test Coverage" 


