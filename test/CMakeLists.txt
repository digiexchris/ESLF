cmake_minimum_required(VERSION 3.5.0)
project(elsf_unit_tests LANGUAGES CXX)

cmake_policy(SET CMP0135 NEW)

include(CTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   # Force use of static runtime library even in Debug configuration
#   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -O1 -g -MT")
#   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fsanitize=address -fno-omit-frame-pointer -O2 -g -MT")
# endif()

  # # ASan flags
  # set(ASAN_FLAGS "-fsanitize=address -fno-omit-frame-pointer -MT")
  
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g ${ASAN_FLAGS} -Wall")
  # add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
  # set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -static)


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
# add_compile_definitions(LIBDWARF_LIBRARY)
# set(LIBDWARF_LIBRARY ${CMAKE_SOURCE_DIR}/out/build/$(presetName)/src/libdwarf/libdwarf.so)

target_link_libraries(
  elsf_tests
  gtest gtest_main
  GTest::gtest_main
  GTest::gmock_main
  etl
  elsf::elsf
)

foreach(target elsf_tests)
    target_compile_definitions(${target} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
        # Remove unwanted definitions
        -U_DLL -U_MT
    )
endforeach()


include(GoogleTest PUBLIC)
#  find_package(PkgConfig)
#  pkg_search_module(GTEST REQUIRED gtest_main)
#  target_link_libraries(elsf_tests PRIVATE ${GTEST_LDFLAGS})
#  target_compile_options(elsf_tests PRIVATE ${GTEST_CFLAGS})
gtest_discover_tests(elsf_tests)
