file(GLOB TEST_SOURCES "**/*.cpp")

file(GLOB LIB_SOURCES "../src/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${LIB_SOURCES}
        ExpressionTests/ExpressionValidationTest.cpp)

target_include_directories(${PROJECT_NAME}_lib PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)


foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_FILE})

    target_include_directories(${TEST_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/include
            ${Boost_INCLUDE_DIRS}
    )

    target_link_libraries(${TEST_NAME} PRIVATE
            ${PROJECT_NAME}_lib
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
            SFML::System
            SFML::Window
            SFML::Graphics
    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    set_target_properties(${TEST_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()