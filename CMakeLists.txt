cmake_minimum_required(VERSION 3.29)
project(GraphGame)

set(CMAKE_CXX_STANDARD 23)

file(GLOB source_files "src/*.cpp")

set(SOURCES ${source_files})

add_executable(${PROJECT_NAME} ${SOURCES})

file(COPY resources/ARIAL.TTF DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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

target_include_directories(${PROJECT_NAME} PRIVATE "include" "lib")

target_link_libraries(${PROJECT_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DIR}/../../../bin"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)