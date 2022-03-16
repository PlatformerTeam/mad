set(
        SOURCES_GAME
        example.cpp
)

add_executable(${EXECUTABLE_GAME} ${SOURCES_GAME})


target_include_directories(${EXECUTABLE_GAME} PUBLIC ${INCLUDE_CORE})
target_link_libraries(${EXECUTABLE_GAME} ${LIBRARY_CORE})
