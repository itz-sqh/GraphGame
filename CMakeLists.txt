cmake_minimum_required(VERSION 3.29)
project(GraphGame)

set(CMAKE_CXX_STANDARD 23)
add_executable(GraphGame src/main.cpp)


find_package(SFML 3.0 COMPONENTS System Window Graphics Audio REQUIRED
        PATHS
        ${SFML_DIR}
        "$ENV{SFML_DIR}"
        "/usr/local"
        "C:/SFML"
        "C:/Program Files/SFML"
        PATH_SUFFIXES "lib/cmake/SFML" REQUIRED
)

if(NOT SFML_FOUND)
    message(WARNING "SFML not found. Please install it to drive C")
endif()


target_link_libraries(GraphGame PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
)

add_custom_command(TARGET GraphGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/../../../bin"
        $<TARGET_FILE_DIR:GraphGame>
)