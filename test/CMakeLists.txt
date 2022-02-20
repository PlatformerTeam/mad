set(
        SOURCES_TEST
        test.cpp
)

add_executable(${EXECUTABLE_TEST} ${SOURCES_TEST})

target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_CORE})
target_link_libraries(${EXECUTABLE_TEST} ${LIBRARY_CORE})

target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_GTEST})
target_link_libraries(${EXECUTABLE_TEST} ${LIBRARY_GTEST})
