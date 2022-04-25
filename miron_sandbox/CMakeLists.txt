set(
        SOURCES_SANDBOX
        sandbox.cpp
)

add_executable(${EXECUTABLE_SANDBOX} ${SOURCES_SANDBOX})

target_include_directories(${EXECUTABLE_SANDBOX} PUBLIC ${INCLUDE_CORE})
target_link_libraries(${EXECUTABLE_SANDBOX} ${LIBRARY_CORE})
