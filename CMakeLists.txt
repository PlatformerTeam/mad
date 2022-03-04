cmake_minimum_required(VERSION 3.19)
project(mad)

set(CMAKE_CXX_STANDARD 17)

#SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(
        LIBRARY_SFML
        sfml-graphics
        sfml-audio
)

#OpenGL
find_package(OpenGL REQUIRED)
set(LIBRARY_OPENGL ${OPENGL_LIBRARIES})

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
set(SOURCES_IMGUI
        ${DIRECTORY_IMGUI}/imgui.cpp
        ${DIRECTORY_IMGUI}/imgui_widgets.cpp
        ${DIRECTORY_IMGUI}/imgui_draw.cpp
        ${DIRECTORY_IMGUI}/imgui_tables.cpp
        ${DIRECTORY_IMGUI}/imgui_demo.cpp)



message(STATUS "ImGui include: ${INCLUDE_IMGUI}")
message(STATUS "ImGui library: ${LIBRARY_IMGUI}")

# ImGui-sfml library
set(IMGUI_DIR ${DIRECTORY_IMGUI})
set(DIRECTORY_IMGUI_SFML ${PROJECT_SOURCE_DIR}/deps/imgui-sfml)
set(INCLUDE_IMGUI_SFML ${DIRECTORY_IMGUI_SFML})
set(SOURCES_IMGUI_SFML ${DIRECTORY_IMGUI_SFML}/imgui-SFML.cpp)

message(STATUS "ImGui-sfml include: ${INCLUDE_IMGUI_SFML}")
message(STATUS "ImGui-sfml library: ${LIBRARY_IMGUI_SFML}")

# Spdlog library
set(DIRECTORY_SPDLOG ${PROJECT_SOURCE_DIR}/deps/spdlog)
set(INCLUDE_SPDLOG ${DIRECTORY_SPDLOG}/include)
set(LIBRARY_SPDLOG spdlog)

add_subdirectory(${DIRECTORY_SPDLOG})
message(STATUS "Spdlog include: ${INCLUDE_SPDLOG}")
message(STATUS "Spdlog library: ${LIBRARY_SPDLOG}")

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
