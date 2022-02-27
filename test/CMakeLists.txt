set(
        SOURCES_TEST
        test.cpp
)

add_executable(${EXECUTABLE_TEST} ${SOURCES_TEST})

# Core library
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_CORE})
target_link_libraries(${EXECUTABLE_TEST} ${LIBRARY_CORE})

# Gtest library
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_GTEST})
target_link_libraries(${EXECUTABLE_TEST} ${LIBRARY_GTEST})

# Spdlog library
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_SPDLOG})
target_link_libraries(${EXECUTABLE_TEST} ${LIBRARY_SPDLOG})

#SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${EXECUTABLE_TEST} sfml-graphics sfml-audio)

# test check use box2d for physics
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_BOX2D})
target_link_libraries(${EXECUTABLE_TEST}  ${LIBRARY_BOX2D})

# test check use box2d for physics
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_IM})
target_link_libraries(${EXECUTABLE_TEST}  ${LIBRARY_BOX2D})

# test check use spdlog for logging
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_SPDLOG})
target_link_libraries(${EXECUTABLE_TEST}  ${LIBRARY_SPDLOG})
