set(
        SOURCES_CORE_COMMON

        common/Error.cpp
)

set(
        SOURCES_CORE

        Core.cpp
        ${SOURCES_CORE_COMMON}
)

add_library(${LIBRARY_CORE} STATIC ${SOURCES_CORE})

# Core headers
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_CORE})

# Core library uses box2d for physics
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_BOX2D})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_BOX2D})

# Core library uses imgui for interface
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_IMGUI})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_IMGUI})

# Core library uses spdlog for logging
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_SPDLOG})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_SPDLOG})
