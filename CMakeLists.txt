# CMakeList.txt : CMake project for ELSF, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)
set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_ESLF_TESTS "Build unit tests" OFF)

project ("ELSF")

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS})
# This allows users which use the add_subdirectory or FetchContent
# to use the same target as users which use find_package
add_library(elsf::elsf ALIAS ${PROJECT_NAME})

if(BUILD_ESLF_TESTS)
  option(EXPOSE_COVERAGE_TARGET "Enable coverage reporting" OFF)

  if(EXPOSE_COVERAGE_TARGET AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate)
  endif()
endif()

target_include_directories(${PROJECT_NAME} ${INCLUDE_SPECIFIER} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

set_property(TARGET ELSF PROPERTY CXX_STANDARD 17)

if((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
  if((${CMAKE_CXX_COMPILER_VERSION} VERSION_EQUAL 11) OR
     (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER 11))
      set(EXPOSE_COVERAGE_TARGET TRUE CACHE BOOL
        "A 'coverage' target will be created and can be used to create a `coverage.json` file containing coverage information in the build tree directory.")
  endif()
endif()

subdirs("coverage")

#add_subdirectory(lib/etl)
add_subdirectory(lib/fmt)

set(BOOST_ROOT "./lib/boost")
FIND_PACKAGE( Boost 1.82.0 REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

TARGET_LINK_LIBRARIES( ELSF LINK_PUBLIC ${Boost_LIBRARIES} )
target_link_libraries(ELSF PRIVATE fmt::fmt Boost::boost)

if (BOOST_ENABLE_ASSERT_DEBUG_HANDLER)
  target_compile_definitions(ELSF PRIVATE BOOST_ENABLE_ASSERT_DEBUG_HANDLER=${BOOST_ENABLE_ASSERT_DEBUG_HANDLER})
endif()

if (BOOST_ENABLE_ASSERT_HANDLER)
  target_compile_definitions(ELSF PRIVATE BOOST_ENABLE_ASSERT_HANDLER=${BOOST_ENABLE_ASSERT_HANDLER})
endif()

# TODO: Add tests and install targets if needed.
if (BUILD_ESLF_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()