cmake_minimum_required(VERSION 3.5.0)
project(elsf_unit_tests LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(elsf_tests
	Encoder/test_Encoder.cpp
	State/Machine/test_Init.cpp
  )

target_compile_definitions(elsf_tests PRIVATE -Delsf_DEBUG)
enable_testing()

include_directories(./)

target_link_libraries(
  elsf_tests
  GTest::gtest_main
  etl
)

include(GoogleTest PUBLIC)
gtest_discover_tests(elsf_tests)
