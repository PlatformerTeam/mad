function(test_executable EXECUTABLE_TEST_NAME EXECUTABLE_SOURCES)
    message(STATUS "Test executable: '${EXECUTABLE_TEST_NAME}' is built with ${EXECUTABLE_SOURCES}")

    add_executable(
            ${EXECUTABLE_TEST_NAME}
            ${EXECUTABLE_SOURCES}
            ${SOURCES_IMGUI}
            ${SOURCES_IMGUI_SFML}
    )

    target_include_directories(
            ${EXECUTABLE_TEST_NAME} PUBLIC

            ${PROJECT_SOURCE_DIR}
            ${INCLUDE_GTEST}
            ${INCLUDE_SPDLOG}
            ${INCLUDE_BOX2D}
            ${INCLUDE_IMGUI}
            ${INCLUDE_IMGUI_SFML}
    )

    target_link_libraries(
            ${EXECUTABLE_TEST_NAME}

            ${LIBRARY_SFML}
            ${LIBRARY_CORE}
            ${LIBRARY_GTEST}
            ${LIBRARY_SPDLOG}
            ${LIBRARY_BOX2D}
            ${LIBRARY_OPENGL}
    )
endfunction()

set(
        SOURCES_TEST_CORE

        core/TestCore.cpp
)

set(
        SOURCES_TEST

        test.cpp
        ${SOURCES_TEST_CORE}
)

test_executable(${EXECUTABLE_TEST} "${SOURCES_TEST}")

add_subdirectory(deps)
