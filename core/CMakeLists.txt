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
        event/management/controller/Controller.hpp
        event/management/controller/CameraController.cpp event/management/controller/CameraController.hpp
        event/management/condition/Condition.hpp
        event/management/controller/statemachine/condition/TrueCondition.hpp
        event/management/dispatcher/EventDispatcher.hpp
        event/management/dispatcher/ImmediateDispatcher.hpp
        event/management/dispatcher/ImmediateDispatcher.cpp
        event/management/handler/EventHandler.hpp
        event/management/handler/WindowCloseHandler.hpp event/management/handler/WindowCloseHandler.cpp
        event/management/handler/MainMenuEventsHandler.hpp event/management/handler/MainMenuEventsHandler.cpp
        event/management/handler/PauseMenuEventsHandler.hpp event/management/handler/PauseMenuEventsHandler.cpp
        event/management/handler/LevelRunnerEventsHandler.hpp event/management/handler/LevelRunnerEventsHandler.cpp
        event/management/handler/GameRunnerEventsHandler.hpp event/management/handler/GameRunnerEventsHandler.cpp
        event/management/producer/SystemListener.cpp event/management/producer/SystemListener.hpp
        event/management/producer/EventProducer.hpp
        event/management/dispatcher/DelayedDispatcher.cpp event/management/dispatcher/DelayedDispatcher.hpp
        event/menu/MenuEvent.hpp event/menu/MenuEvent.cpp
        event/menu/MainMenuEvent.hpp event/menu/MainMenuEvent.cpp
        event/menu/PauseMenuEvent.hpp event/menu/PauseMenuEvent.cpp
        event/runner/RunnerEvent.hpp event/runner/RunnerEvent.cpp
        event/runner/GameRunnerEvent.hpp event/runner/GameRunnerEvent.cpp
        event/runner/LevelRunnerEvent.hpp event/runner/LevelRunnerEvent.cpp
        event/management/controller/Controller.hpp
        event/management/controller/statemachine/StateMachine.hpp
        event/management/controller/statemachine/StateMachine.cpp
        event/management/controller/statemachine/condition/Condition.hpp

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
        loader/LevelLoaderFromFile.cpp loader/LevelLoaderFromFile.hpp

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
        event/management/condition/TrueCondition.hpp event/management/condition/TrueCondition.cpp)

add_library(
        ${LIBRARY_CORE} STATIC

        ${SOURCES_CORE}
        ${SOURCES_IMGUI}
        ${SOURCES_IMGUI_SFML}
)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${LIBRARY_CORE} PUBLIC SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
    message(STATUS "Enable debug logs for ${LIBRARY_CORE}")
endif ()

target_include_directories(
        ${LIBRARY_CORE} PUBLIC

        ${INCLUDE_CORE}
        ${INCLUDE_BOX2D}
        ${INCLUDE_SFML}
        ${INCLUDE_IMGUI}
        ${INCLUDE_IMGUI_SFML}
        ${INCLUDE_SPDLOG}
        ${INCLUDE_JSON}
)

target_link_libraries(
        ${LIBRARY_CORE}

        ${LIBRARY_SFML}
        ${LIBRARY_SPDLOG}
        ${LIBRARY_BOX2D}
        ${LIBRARY_OPENGL}
        ${LIBRARY_JSON}
)
