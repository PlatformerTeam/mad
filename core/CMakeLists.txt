set(
        SOURCES_CORE
        Core.cpp
)

add_library(${LIBRARY_CORE} STATIC ${SOURCES_CORE})

# Core headers
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_CORE})

# Core libray uses box2d for physics
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_BOX2D})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_BOX2D})
