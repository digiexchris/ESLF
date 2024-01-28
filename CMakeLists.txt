# CMakeList.txt : CMake project for ELSF, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(BUILD_ESLF_TESTS "Build unit tests" OFF)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.8.0")
cmake_policy(SET CMP0135 NEW)
endif()

project ("ELSF")

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} src/Encoder/IEncoder.cpp src/State/Machine/Machine.cpp src/State/Machine/EStop.cpp src/State/Machine/Idle.cpp src/State/Machine/Running.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# This allows users which use the add_subdirectory or FetchContent
# to use the same target as users which use find_package
add_library(elsf::elsf ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} ${INCLUDE_SPECIFIER} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ELSF PROPERTY CXX_STANDARD 17)
endif()

add_subdirectory(lib/etl)
target_link_libraries(ELSF PRIVATE etl)

# TODO: Add tests and install targets if needed.
if (BUILD_ESLF_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()