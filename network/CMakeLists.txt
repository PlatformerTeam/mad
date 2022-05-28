function(network_executable EXECUTABLE_NETWORK_NAME EXECUTABLE_SOURCES)
    message(STATUS "Network executable: '${EXECUTABLE_NETWORK_NAME}' is built with ${EXECUTABLE_SOURCES}")

    add_executable(
            ${EXECUTABLE_NETWORK_NAME}
            ${EXECUTABLE_SOURCES}
            ${SOURCES_IMGUI}
            ${SOURCES_IMGUI_SFML}
    )

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_definitions(${EXECUTABLE_NETWORK_NAME} PUBLIC SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
        message(STATUS "Enable debug logs for ${EXECUTABLE_NETWORK_NAME}")
    endif()

    target_include_directories(
            ${EXECUTABLE_NETWORK_NAME} PUBLIC

            ${PROJECT_SOURCE_DIR}
            ${INCLUDE_SPDLOG}
            ${INCLUDE_BOX2D}
            ${INCLUDE_IMGUI}
            ${INCLUDE_IMGUI_SFML}
            ${INCLUDE_HTTP}
    )

    target_link_libraries(
            ${EXECUTABLE_NETWORK_NAME}

            ${LIBRARY_SFML}
            ${LIBRARY_CORE}
            ${LIBRARY_SPDLOG}
            ${LIBRARY_BOX2D}
            ${LIBRARY_OPENGL}
            ${LIBRARY_PQXX}
    )

endfunction()

network_executable(${EXECUTABLE_SERVER} server/server.cpp)
network_executable(${EXECUTABLE_CLIENT} client/client.cpp)
