gtest_dep = dependency('gtest', main : true)
gmock_dep = dependency('gmock', main : true)

test_src_files = files('Encoder/test_Encoder.cpp',
                       'Logger/test_logger.cpp',
                       'State/Machine/test_init.cpp',
                       'main.cpp',
                       # Add all other test source files here
                      )

elsf_tests = executable('elsf_tests',
  test_src_files,
  dependencies : [gtest_dep, gmock_dep, elsf_lib],
  install : false
)

test('elsf_unit_tests', elsf_tests)
