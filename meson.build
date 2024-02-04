project('ELSF', 'cpp', version: '0.1', default_options: ['cpp_std=c++17'])

sources = files('src/Encoder/IEncoder.cpp',
                'src/State/Machine/Machine.cpp',
                'src/State/Machine/EStop.cpp',
                'src/State/Machine/Idle.cpp',
                'src/State/Machine/Running.cpp')

#include_directories('lib/etl/include')

etl_dep = subproject('etl').get_variable('etl_dep')

inc_dirs = include_directories('include')

elsf_lib = library('ELSF', sources, include_directories : inc_dirs)

elsf_dep = declare_dependency(
    include_directories: inc_dirs,
    link_with: elsf_lib,
    dependencies: [etl_dep]
)

# ETL is added as a subproject or system dependency
# etl_dep = dependency('etl', fallback: ['etl', 'etl_dep'])

if get_option('build_tests')
  subdir('test')
endif
