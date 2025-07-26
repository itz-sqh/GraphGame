cmake_minimum_required(VERSION 3.31)
project(GraphGame)

set(CMAKE_CXX_STANDARD 23)

file(GLOB source_files "src/*.cpp")
add_executable(${PROJECT_NAME} ${source_files})

file(COPY resources/ARIAL.TTF DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE "include")


find_package(SFML 3.0 COMPONENTS System Window Graphics REQUIRED
        PATHS
        ${SFML_DIR}
        "$ENV{SFML_DIR}"
        "C:/SFML"
        "C:/Program Files/SFML"
        PATH_SUFFIXES "lib/cmake/SFML"
)

if (NOT SFML_FOUND)
    message(WARNING "SFML not found. Please install it to C:/SFML or C:/Program Files/SFML")
endif ()


target_link_libraries(${PROJECT_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
)

find_package(Boost 1.74 QUIET COMPONENTS unit_test_framework)
if (Boost_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    enable_testing()
    add_subdirectory(tests)
endif ()
