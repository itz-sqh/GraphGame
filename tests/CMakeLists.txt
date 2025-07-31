file(GLOB_RECURSE TEST_SOURCES "*.cpp")

file(GLOB_RECURSE LIB_SOURCES
        "../${SOURCE_DIR}/core/*.cpp"
        "../${SOURCE_DIR}/expression/*.cpp"
        "../${SOURCE_DIR}/math/*.cpp"
        "../${SOURCE_DIR}/objects/*.cpp"
        "../${SOURCE_DIR}/*.cpp"
)

add_library(${PROJECT_NAME}_test_lib STATIC ${LIB_SOURCES})

target_include_directories(${PROJECT_NAME}_test_lib PRIVATE
        ${CMAKE_SOURCE_DIR}/${INCLUDE_DIR}
)

foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_FILE})

    target_include_directories(${TEST_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/${INCLUDE_DIR}
            ${Boost_INCLUDE_DIRS}
    )

    target_link_libraries(${TEST_NAME} PRIVATE
            ${PROJECT_NAME}_test_lib
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
            Boost::serialization
            SFML::System
            SFML::Graphics

    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    set_target_properties(${TEST_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
endforeach()