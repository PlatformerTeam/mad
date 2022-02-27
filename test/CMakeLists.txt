set(
        SOURCES_TEST
        test.cpp
)

add_executable(${EXECUTABLE_TEST} ${SOURCES_TEST} ${SOURCES_IMGUI} ${SOURCES_IMGUI_SFML})

target_link_libraries(${EXECUTABLE_TEST}  sfml-graphics sfml-audio)

target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_CORE})
target_link_libraries(${EXECUTABLE_TEST} ${LIBRARY_CORE})


# test check use box2d for physics
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_BOX2D})
target_link_libraries(${EXECUTABLE_TEST}  ${LIBRARY_BOX2D})

# test check use imgui
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_IMGUI})

# test check use imgui-sfml
target_include_directories(${EXECUTABLE_TEST} PUBLIC ${INCLUDE_IMGUI_SFML})

# OpenGL
target_link_libraries(${EXECUTABLE_TEST}  ${OPENGL_LIBRARIES})

# uncomment ONE for open test windows
#add_definitions(-DBOX2D_TEST_WINDOW)
#add_definitions(-DIMGUI_TEST_WINDOW)
