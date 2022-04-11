set(
        EXAMPLE_GAME
        example.cpp
)

set(
        GAME_RUNNER_EXAMPLE
        game_runner_example.cpp
)

add_executable(${EXECUTABLE_GAME} ${EXAMPLE_GAME})
add_executable(${EXECUTABLE_GAME_RUNNER} ${GAME_RUNNER_EXAMPLE})

target_include_directories(${EXECUTABLE_GAME} PUBLIC ${INCLUDE_CORE})
target_link_libraries(${EXECUTABLE_GAME} ${LIBRARY_CORE})
