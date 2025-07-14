cmake_minimum_required(VERSION 3.29)
project(GraphGame)

set(CMAKE_CXX_STANDARD 23)
add_executable(GraphGame src/main.cpp
        src/ExpressionParser/ExpressionParser.cpp
        src/ExpressionParser/ExpressionParser.h
        src/ExpressionParser/Expression.cpp
        src/ExpressionParser/Expression.h
        src/ExpressionParser/Token.cpp
        src/ExpressionParser/Token.h
        src/ExpressionParser/constants.h
        src/GameConstants.h
        src/GameConstants.h
        src/PointGenerator/PointGenerator.cpp
        src/PointGenerator/PointGenerator.h
        src/FunctionPlotter/FunctionPlotter.cpp
        src/FunctionPlotter/FunctionPlotter.h
        src/Game.cpp
        src/Game.h
        src/Player.cpp
        src/Player.h
        src/Obstacle.cpp
        src/Obstacle.h
        src/rng.cpp
        src/rng.h
        src/CircleObject.cpp
        src/CircleObject.h
        src/ExpressionParser/ExpressionException.cpp
        src/ExpressionParser/ExpressionException.h
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/ARIAL.TTF  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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