cmake_minimum_required(VERSION 3.5.0)
project(elsf_unit_tests LANGUAGES CXX)

include(CTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

FetchContent_Declare(
  trompeloeil
  GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
  GIT_TAG        v47 # or a later release
)
FetchContent_MakeAvailable(trompeloeil)

file(GLOB_RECURSE TESTS ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_executable(elsf_tests
  ${TESTS}
  )

target_compile_definitions(elsf_tests PRIVATE -DELSF_DEBUG)

enable_testing()

include_directories(./)

if(EXPOSE_COVERAGE_TARGET AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
target_link_libraries(
  elsf_tests PRIVATE -fprofile-instr-generate
  Catch2::Catch2WithMain
  trompeloeil::trompeloeil
  # etl
  elsf::elsf
  fmt::fmt
)
else()
target_link_libraries(
  elsf_tests PRIVATE
  Catch2::Catch2WithMain
  trompeloeil::trompeloeil
  etl
  elsf::elsf
  fmt::fmt
)
endif()



target_compile_definitions(elsf_tests PRIVATE
 -DCATCH_CONFIG_POSIX_SIGNALS
 -DCATCH_CONFIG_EXPERIMENTAL_REDIRECT
                              )


catch_discover_tests(elsf_tests)
