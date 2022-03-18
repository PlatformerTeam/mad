set(
        SOURCES_CORE

        common/Error.cpp common/Error.hpp
        common/FVec2D.cpp common/FVec2D.hpp
        common/Color.cpp common/Color.hpp
        common/Cast.hpp

        event/Event.cpp
        event/visual/VisualEvent.cpp event/visual/VisualEvent.hpp
        event/visual/PositionalAppearance.cpp event/visual/PositionalAppearance.hpp
        event/system/KeyPressed.hpp event/system/KeyPressed.cpp
        event/system/KeyReleased.hpp event/system/KeyReleased.cpp
        event/system/KeyHeld.hpp event/system/KeyHeld.cpp
        event/management/dispatcher/EventDispatcher.hpp
        event/management/dispatcher/ImmediateDispatcher.hpp
        event/management/dispatcher/ImmediateDispatcher.cpp
        event/management/EventHandler.hpp
        event/management/EventProducer.cpp event/management/EventProducer.hpp
        event/management/dispatcher/DelayedDispatcher.cpp event/management/dispatcher/DelayedDispatcher.hpp

        world/World.cpp world/World.hpp
        world/LocalWorld.cpp world/LocalWorld.hpp
        world/filter/Filter.hpp
        world/filter/TrueFilter.hpp
        world/filter/IdFilter.hpp
        world/entity/EntityStorage.cpp world/entity/EntityStorage.hpp
        world/entity/ViewableEntity.hpp world/entity/ViewableEntity.cpp
        world/entity/Entity.hpp world/entity/Entity.cpp
        world/intent/Intent.cpp world/intent/Intent.hpp
        world/intent/LambdaIntent.cpp world/intent/LambdaIntent.hpp
        world/intent/Intent.cpp world/intent/Intent.hpp
        world/entity/PhysicalEntity.hpp world/entity/PhysicalEntity.cpp

        system/SystemListener.cpp system/SystemListener.hpp

        runner/GameRunner.hpp
        runner/SequentialRunner.cpp runner/SequentialRunner.hpp

        visual/image/Image.hpp
        visual/image/shape/Shape.cpp visual/image/shape/Shape.hpp
        visual/image/shape/Square.cpp visual/image/shape/Square.hpp
        visual/image/static/StaticImage.cpp visual/image/static/StaticImage.hpp
        visual/Renderable.hpp
        visual/Camera.cpp visual/Camera.hpp
)

add_library(${LIBRARY_CORE} SHARED ${SOURCES_CORE})

# Core headers
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_CORE})

# Core librayr uses sfml
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_SFML})

# Core library uses box2d for physics
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_BOX2D})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_BOX2D})

# Core library uses SFML for interface
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_SFML})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_SFML})

# Core library uses imgui for interface
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_IMGUI})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_IMGUI})

# Core library uses imgui-SFML for interface
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_IMGUI_SFML})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_IMGUI_SFML})

# Core library uses spdlog for logging
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_SPDLOG})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_SPDLOG})
