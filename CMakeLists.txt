cmake_minimum_required(VERSION 3.29)
project(GraphGame)

set(CMAKE_CXX_STANDARD 23)
add_executable(GraphGame src/main.cpp
        src/ExpressionParser.cpp
        include/ExpressionParser.h
        src/Expression.cpp
        include/Expression.h
        src/Token.cpp
        include/Token.h
        include/constants.h
        include/GameConstants.h
        include/GameConstants.h
        src/PointGenerator.cpp
        include/PointGenerator.h
        src/FunctionPlotter.cpp
        include/FunctionPlotter.h
        src/Game.cpp
        include/Game.h
        src/Player.cpp
        include/Player.h
        src/Obstacle.cpp
        include/Obstacle.h
        src/rng.cpp
        include/Rng.h
        src/CircleObject.cpp
        include/CircleObject.h
        src/ExpressionException.cpp
        include/ExpressionException.h
        src/Geometry.cpp
        include/Geometry.h
)

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