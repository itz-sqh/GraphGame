file(GLOB_RECURSE SOURCES
        "*.cpp"
        "**/*.cpp"
)


file(GLOB_RECURSE HEADERS
        "../${INCLUDE_DIR}/*.h"
        "../${INCLUDE_DIR}/**/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS}
        ../include/ui/MenuComponent.h
        ../include/ui/MenuTextItem.h
        ../include/ui/MenuContainer.h
        ui/MenuTextItem.cpp
        ui/MenuContainer.cpp)

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