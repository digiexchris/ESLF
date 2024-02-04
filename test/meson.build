
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
etl_dep = subproject('etl').get_variable('etl_dep')
# elsf_dep = elsf_lib.get_variable('elsf_dep')

test_sources = files('Encoder/test_Encoder.cpp',
                     'Logger/test_logger.cpp',
                     'State/Machine/test_init.cpp',
                     'main.cpp')
# root_inc_dirs = meson.current_source_dir().get_variable('inc_dirs')
# include_directories = include_directories(root_inc_dirs)

elsf_tests = executable('elsf_tests',
                        test_sources,
                        dependencies : [
                            gtest_dep,
                            gmock_dep,
                            etl_dep,
                            elsf_dep
                        ],
                        link_with: elsf_lib,
                        cpp_args: '-DELSF_DEBUG')

test('elsf_unit_tests', elsf_tests)
