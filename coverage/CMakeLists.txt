if(${EXPOSE_COVERAGE_TARGET})
  # specific flags to build the covered project. Enable source based Coverage
  # see:
  # https://releases.llvm.org/11.0.0/tools/clang/docs/SourceBasedCodeCoverage.html
#   target_compile_options(elsf::elsf PRIVATE
#                          -fprofile-instr-generate -fcoverage-mapping)
#   target_link_options(elsf::elsf PRIVATE
#                       -fprofile-instr-generate -fcoverage-mapping)

  # Useful variables used later, specific to llvm tools path and output
  # directory
  get_filename_component(llvmBinPath ${CMAKE_CXX_COMPILER} DIRECTORY)
  set(llvmProfData ${llvmBinPath}/llvm-profdata)
  set(llvmCov ${llvmBinPath}/llvm-cov)

  # An internal custom command used as dependency of exposed targets to
  # generate coverage data
  add_custom_command(OUTPUT default.profdata
                     DEPENDS .elsf_testsuites.executed
                     COMMAND ${llvmProfData}
                       ARGS merge 
                       -sparse
                       $<TARGET_NAME_IF_EXISTS:elsf_tests>.profraw
                       -o default.profdata)

  # An internal command used as dependency for exposed targets. Ensures that
  # test suites have been executed with latest modifications and latest
  # coverage data.
  add_custom_command(OUTPUT .elsf_testsuites.executed
                     DEPENDS
                       elsf::elsf elsf_tests
                     COMMAND ${CMAKE_COMMAND}
                       ARGS -E copy $<TARGET_FILE:elsf::elsf> $<TARGET_FILE_DIR:elsf_tests>
                     COMMAND $<TARGET_FILE:elsf_tests>
                     COMMAND ${CMAKE_COMMAND}
                       ARGS -E rename default.profraw $<TARGET_NAME_IF_EXISTS:elsf_tests>.profraw
                     COMMAND ${CMAKE_COMMAND}
                       ARGS -E touch .elsf_testsuites.executed
                     VERBATIM
                     USES_TERMINAL)

  # A target to generate detailed coverage information in json format. To get
  # a grab on ow it is structured, see:
  # https://stackoverflow.com/questions/56013927/how-to-read-llvm-cov-json-format
  # https://llvm.org/doxygen/structllvm_1_1coverage_1_1CoverageSegment.html
  # https://llvm.org/doxygen/structllvm_1_1coverage_1_1CounterMappingRegion.html
  # https://github.com/llvm/llvm-project/blob/aa4e6a609acdd00e06b54f525054bd5cf3624f0f/llvm/tools/llvm-cov/CoverageExporterJson.cpp#L15
  add_custom_target(coverage
                    DEPENDS coverage.json)

  # An internal command used to generate detailed coverage information in a
  # file
  add_custom_command(OUTPUT coverage.json
                     DEPENDS default.profdata
                     COMMAND ${llvmCov}
                       ARGS export --format=text
                       --object=$<TARGET_FILE:elsf_tests>
                       --instr-profile=default.profdata
                       > coverage.json
                     VERBATIM
                     USES_TERMINAL)
endif()