project('ELSF', 'cpp',
  version : '0.1',
  default_options : ['cpp_std=c++17'])

# Dependencies
etl_dep = dependency('etl', fallback : ['etl', 'etl_dep'])

# Main library target
src_files = files('src/State/Machine/Machine.cpp',
                  'src/State/Machine/Idle.cpp',
                  # Add all other source files here
                 )
inc_dirs = include_directories('include')

elsf_lib = library('elsf',
  src_files,
  include_directories : inc_dirs,
  dependencies : etl_dep,
  install : true
)

# Conditionally include tests
if get_option('build_tests')
  subdir('test')
endif
