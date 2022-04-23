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
        event/system/WindowClose.hpp event/system/WindowClose.cpp
        event/system/KeyHeld.hpp event/system/KeyHeld.cpp
        event/system/LevelPause.hpp event/system/LevelPause.cpp
        event/management/dispatcher/EventDispatcher.hpp
        event/management/dispatcher/ImmediateDispatcher.hpp
        event/management/dispatcher/ImmediateDispatcher.cpp
        event/management/handler/EventHandler.hpp
        event/management/handler/WindowCloseHandler.hpp event/management/handler/WindowCloseHandler.cpp
        event/management/handler/LevelPauseHandler.hpp event/management/handler/LevelPauseHandler.cpp
        event/management/handler/MainMenuEventsHandler.hpp event/management/handler/MainMenuEventsHandler.cpp
        event/management/handler/PauseMenuEventsHandler.hpp event/management/handler/PauseMenuEventsHandler.cpp
        event/management/producer/SystemListener.cpp event/management/producer/SystemListener.hpp
        event/management/producer/EventProducer.hpp
        event/management/dispatcher/DelayedDispatcher.cpp event/management/dispatcher/DelayedDispatcher.hpp
        event/menu/MenuEvent.hpp event/menu/MenuEvent.cpp
        event/menu/MainMenuEvent.hpp event/menu/MainMenuEvent.cpp
        event/menu/PauseMenuEvent.hpp event/menu/PauseMenuEvent.cpp

        event/management/handler/CollisionHandler.hpp event/management/handler/CollisionHandler.cpp
        event/physics/Collision.hpp event/physics/Collision.cpp

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
        world/entity/ContactListener/ContactListener.hpp

        menu/Menu.hpp menu/Menu.cpp
        menu/MainMenu.hpp menu/MainMenu.cpp
        menu/PauseMenu.hpp menu/PauseMenu.cpp

        runner/Runner.hpp
        runner/SequentialRunner.cpp runner/SequentialRunner.hpp
        runner/LevelRunner.hpp runner/LevelRunner.cpp
        runner/GameRunner.hpp runner/GameRunner.cpp
        loader/LevelLoader.hpp

        visual/image/Image.hpp
        visual/image/static/RenderableStatic.cpp visual/image/static/RenderableStatic.hpp
        visual/image/shape/square/RenderableSquare.cpp visual/image/shape/square/RenderableSquare.hpp
        visual/image/animated/RenderableAnimated.cpp visual/image/animated/RenderableAnimated.hpp
        visual/image/shape/Shape.cpp visual/image/shape/Shape.hpp
        visual/image/shape/square/Square.cpp visual/image/shape/square/Square.hpp
        visual/image/static/StaticImage.cpp visual/image/static/StaticImage.hpp
        visual/image/animated/AnimatedImage.cpp visual/image/animated/AnimatedImage.hpp
        visual/Renderable.hpp
        visual/Camera.cpp visual/Camera.hpp
)

add_library(
        ${LIBRARY_CORE} SHARED

        ${SOURCES_CORE}
        ${SOURCES_IMGUI}
        ${SOURCES_IMGUI_SFML}
)

# Core headers
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_CORE})

# Core library uses box2d for physics
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_BOX2D})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_BOX2D})

# Core library uses SFML for interface
target_include_directories(${LIBRARY_CORE} PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_SFML})

# Core library uses imgui for gui
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_IMGUI})

# Core library uses OpenGL as a graphics backend
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_OPENGL})

# Core library uses imgui-SFML for interface
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_IMGUI_SFML})

# Core library uses spdlog for logging
target_include_directories(${LIBRARY_CORE} PUBLIC ${INCLUDE_SPDLOG})
target_link_libraries(${LIBRARY_CORE} ${LIBRARY_SPDLOG})
