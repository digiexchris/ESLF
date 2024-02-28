# CMakeList.txt : CMake project for ELSF, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_ESLF_TESTS "Build unit tests" OFF)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  if(MSVC)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
  endif()

endif()

project ("ELSF")

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
# This allows users which use the add_subdirectory or FetchContent
# to use the same target as users which use find_package
add_library(elsf::elsf ALIAS ${PROJECT_NAME})

if(BUILD_ESLF_TESTS)
  option(EXPOSE_COVERAGE_TARGET "Enable coverage reporting" OFF)

  if(EXPOSE_COVERAGE_TARGET AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate)
    # # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    # # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-instr-generate")
  endif()
endif()

target_include_directories(${PROJECT_NAME} ${INCLUDE_SPECIFIER} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ELSF PROPERTY CXX_STANDARD 17)
endif()

if((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
  if((${CMAKE_CXX_COMPILER_VERSION} VERSION_EQUAL 11) OR
     (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER 11))
      set(EXPOSE_COVERAGE_TARGET TRUE CACHE BOOL
        "A 'coverage' target will be created and can be used to create a `coverage.json` file containing coverage information in the build tree directory.")
  endif()
endif()

subdirs("coverage")

add_subdirectory(lib/etl)
add_subdirectory(lib/fmt)
target_link_libraries(ELSF PRIVATE etl fmt::fmt)

# TODO: Add tests and install targets if needed.
if (BUILD_ESLF_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()