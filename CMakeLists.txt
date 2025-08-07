cmake_minimum_required(VERSION 3.31)
project(GraphGame)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(RESOURCES_DIR resources)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


find_package(SFML 3.0 COMPONENTS System Window Graphics REQUIRED
        PATHS
        ${SFML_DIR}
        "$ENV{SFML_DIR}"
        "C:/SFML"
        PATH_SUFFIXES "lib/cmake/SFML"
)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found. Please install SFML 3.0+")
endif ()

add_subdirectory(src)

option(BUILD_TESTS "Build tests" OFF)
if (BUILD_TESTS)
    find_package(Boost 1.74 REQUIRED COMPONENTS unit_test_framework)
    enable_testing()
    add_subdirectory(tests)
endif ()

