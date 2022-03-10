set(
        SOURCES_CORE

        common/Error.cpp common/Error.hpp
        common/FVec2D.cpp common/FVec2D.hpp
        common/Color.cpp common/Color.hpp

        visual/Renderable.hpp
        visual/Camera.cpp visual/Camera.hpp

        event/Event.cpp
        event/visual/VisualEvent.cpp event/visual/VisualEvent.hpp
        event/visual/PositionalAppearance.cpp event/visual/PositionalAppearance.hpp
        event/management/EventDispatcher.hpp
        event/management/EventHandler.hpp
        event/management/EventProducer.cpp event/management/EventProducer.hpp

        world/World.hpp
        world/LocalWorld.cpp world/LocalWorld.hpp
        world/filter/Filter.hpp
        world/intent/Intent.cpp world/intent/Intent.hpp
        world/entity/EntityStorage.cpp world/entity/EntityStorage.hpp
        world/intent/Intent.cpp world/intent/Intent.hpp

        system/KeyboardListener.cpp system/KeyboardListener.hpp

        world/entity/Entity.hpp world/entity/Entity.cpp

        runner/GameRunner.hpp
        runner/SequentialRunner.cpp runner/SequentialRunner.hpp
        visual/image/Image.hpp
        visual/image/shape/Shape.cpp visual/image/shape/Shape.hpp
        visual/image/shape/Square.cpp visual/image/shape/Square.hpp
)

add_library(${LIBRARY_CORE} SHARED ${SOURCES_CORE})

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
