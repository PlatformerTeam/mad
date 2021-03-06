#include <database/database/Database.hpp>
#include <database/driver/offline/OfflineClientStorageDriver.hpp>
#include <database/driver/postgresql/DatabaseClientStorageDriver.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/handler/LevelRunnerEventsHandler.hpp>
#include <event/management/handler/AuthorizationMenuEventsHandler.hpp>
#include <event/management/handler/MainMenuEventsHandler.hpp>
#include <event/management/handler/WindowCloseHandler.hpp>
#include <event/management/handler/PauseMenuEventsHandler.hpp>
#include <event/management/handler/GameRunnerEventsHandler.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <event/system/KeyHeld.hpp>
#include <loader/LevelLoader.hpp>
#include <menu/AuthorizationMenu.hpp>
#include <menu/MainMenu.hpp>
#include <menu/PauseMenu.hpp>
#include <runner/GameRunner.hpp>
#include <visual/Camera.hpp>
#include <world/LocalWorld.hpp>
#include <world/entity/ViewableEntity.hpp>
#include <loader/LevelLoader.hpp>
#include <loader/LevelLoaderFromFile.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <spdlog/spdlog.h>

int main() {
#ifndef NDEBUG
    auto log_level = spdlog::level::trace;
#else
    auto log_level = spdlog::level::info;
#endif
    spdlog::set_level(log_level);

    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "MAD");
    ImGui::SFML::Init(*window);
    window->setFramerateLimit(120);

    auto global_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

    auto system_listener = std::make_shared<mad::core::SystemListener>(window);

    auto database = std::make_shared<mad::core::Database>();
    auto database_storage_driver = std::make_shared<mad::core::DatabaseClientStorageDriver>(database);

    std::vector<std::shared_ptr<mad::core::LevelLoader>> level_loaders{
            std::make_shared<mad::core::LevelLoaderFromFile>("../../game/resources/levels/level_01"),
            std::make_shared<mad::core::LevelLoaderFromFile>("../../game/resources/levels/level_02"),
            std::make_shared<mad::core::LevelLoaderFromFile>("../../game/resources/levels/level_03"),
            std::make_shared<mad::core::LevelLoaderFromFile>("../../game/resources/levels/level_with_finish")
    };

    auto game_runner = std::make_unique<mad::core::GameRunner>(
            level_loaders,
            global_dispatcher,
            std::make_unique<mad::core::MainMenu>(),
            std::make_unique<mad::core::AuthorizationMenu>(database_storage_driver),
            system_listener,
            database_storage_driver
    );

    global_dispatcher->registry(std::make_shared<mad::core::WindowCloseHandler>(*window));
    global_dispatcher->registry(std::make_shared<mad::core::MainMenuEventsHandler>(*game_runner));
    global_dispatcher->registry(std::make_shared<mad::core::GameRunnerEventsHandler>(*game_runner, database_storage_driver));
    global_dispatcher->registry(std::make_shared<mad::core::AuthorizationMenuEventsHandler>(*game_runner));

    game_runner->run(*window);

    ImGui::SFML::Shutdown();
}

// sudo apt-get update
// sudo apt-get install postgresql postgresql-contrib
// sudo -i -u postgres
// createuser -P --interactive
// @create user with ubuntu-system username@
// createdb @ubuntu-username@
// createdb mad
