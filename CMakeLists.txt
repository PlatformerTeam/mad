cmake_minimum_required(VERSION 3.20)
project(mad)

set(CMAKE_CXX_STANDARD 17)

# Testing framework
set(DIRECTORY_GTEST ${PROJECT_SOURCE_DIR}/deps/googletest)
set(INCLUDE_GTEST ${DIRECTORY_GTEST}/googletest/include)
set(LIBRARY_GTEST gtest_main)

add_subdirectory(${DIRECTORY_GTEST})
message(STATUS "Gtest include: ${INCLUDE_GTEST}")
message(STATUS "Gtest library: ${LIBRARY_GTEST}")

# Physics library
set(DIRECTORY_BOX2D ${PROJECT_SOURCE_DIR}/deps/box2d)
set(INCLUDE_BOX2D ${DIRECTORY_BOX2D}/include)
set(LIBRARY_BOX2D box2d)

add_subdirectory(${DIRECTORY_BOX2D})
message(STATUS "Box2d include: ${INCLUDE_BOX2D}")
message(STATUS "Box2d library: ${LIBRARY_BOX2D}")

# ImGui library
set(DIRECTORY_IMGUI ${PROJECT_SOURCE_DIR}/deps/imgui)
set(INCLUDE_IMGUI ${DIRECTORY_IMGUI})
set(LIBRARY_IMGUI imgui)

message(STATUS "ImGui include: ${INCLUDE_IMGUI}")
message(STATUS "ImGui library: ${LIBRARY_IMGUI}")

# Core library
set(DIRECTORY_CORE ${PROJECT_SOURCE_DIR}/core)
set(INCLUDE_CORE ${DIRECTORY_CORE})
set(LIBRARY_CORE engine)

add_subdirectory(${DIRECTORY_CORE})
message(STATUS "Core include: ${INCLUDE_CORE}")
message(STATUS "Core library: ${LIBRARY_CORE}")

# Game binaries
set(DIRECTORY_GAME ${PROJECT_SOURCE_DIR}/game)
set(EXECUTABLE_GAME example)

add_subdirectory(${DIRECTORY_GAME})
message(STATUS "Game executable: ${EXECUTABLE_GAME}")

# Tests
set(DIRECTORY_TEST ${PROJECT_SOURCE_DIR}/test)
set(EXECUTABLE_TEST test)

add_subdirectory(${DIRECTORY_TEST})
message(STATUS "Test executable: ${EXECUTABLE_TEST}")
