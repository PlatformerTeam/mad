function(game_executable EXECUTABLE_GAME_NAME EXECUTABLE_SOURCES)
    message(STATUS "Game executable: '${EXECUTABLE_GAME_NAME}' is built with ${EXECUTABLE_SOURCES}")

    add_executable(
            ${EXECUTABLE_GAME_NAME}
            ${EXECUTABLE_SOURCES}
            ${SOURCES_IMGUI}
            ${SOURCES_IMGUI_SFML}
    )

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_definitions(${EXECUTABLE_GAME_NAME} PUBLIC SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
        message(STATUS "Enable debug logs for ${EXECUTABLE_GAME_NAME}")
    endif()

    target_include_directories(
            ${EXECUTABLE_GAME_NAME} PUBLIC

            ${PROJECT_SOURCE_DIR}
            ${INCLUDE_SPDLOG}
            ${INCLUDE_BOX2D}
            ${INCLUDE_IMGUI}
            ${INCLUDE_IMGUI_SFML}
    )

    target_link_libraries(
            ${EXECUTABLE_GAME_NAME}

            ${LIBRARY_SFML}
            ${LIBRARY_CORE}
            ${LIBRARY_SPDLOG}
            ${LIBRARY_BOX2D}
            ${LIBRARY_OPENGL}
            ${LIBRARY_PQXX}
    )

endfunction()

game_executable(${EXECUTABLE_GAME} example.cpp)
#game_executable(${EXECUTABLE_GAME_RUNNER} game_runner_example.cpp)
game_executable(${EXECUTABLE_GAME_RUNNER} game_with_default_loader_example.cpp)
game_executable(${EXECUTABLE_GAME_DATABASE} game_database_example.cpp)
