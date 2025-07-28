file(GLOB_RECURSE SOURCES
        *.cpp
        "core/*.cpp"
        "expression/*.cpp"
        "math/*.cpp"
        "objects/*.cpp"
        "states/*.cpp"
        "ui/*.cpp"
)


file(GLOB_RECURSE HEADERS
        "../${INCLUDE_DIR}/core/*.h"
        "../${INCLUDE_DIR}/expression/*.h"
        "../${INCLUDE_DIR}/math/*.h"
        "../${INCLUDE_DIR}/objects/*.h"
        "../${INCLUDE_DIR}/states/*.h"
        "../${INCLUDE_DIR}/ui/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(TARGET ${PROJECT_NAME})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${RESOURCES_DIR}/
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/${RESOURCES_DIR}/
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/${INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
)


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/${RESOURCES_DIR}/ DESTINATION ${RESOURCES_DIR})