cmake_minimum_required(VERSION 3.5.0)
project(elsf_unit_tests LANGUAGES CXX)

cmake_policy(SET CMP0135 NEW)

include(CTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TESTS ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_executable(elsf_tests
  ${TESTS}
  )

target_compile_definitions(elsf_tests PRIVATE -DELSF_DEBUG)
enable_testing()

include_directories(./)

target_link_libraries(
  elsf_tests
  gtest gtest_main
  GTest::gtest_main
  etl
  elsf::elsf
)
set(GTEST_CATCH_EXCEPTIONS 0)

include(GoogleTest PUBLIC)
#  find_package(PkgConfig)
#  pkg_search_module(GTEST REQUIRED gtest_main)
#  target_link_libraries(elsf_tests PRIVATE ${GTEST_LDFLAGS})
#  target_compile_options(elsf_tests PRIVATE ${GTEST_CFLAGS})
gtest_discover_tests(elsf_tests)
