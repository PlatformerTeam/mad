#include <database/driver/offline/OfflineClientStorageDriver.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/handler/GameRunnerEventsHandler.hpp>
#include <event/management/handler/LevelRunnerEventsHandler.hpp>
#include <event/management/handler/MainMenuEventsHandler.hpp>
#include <event/management/handler/PauseMenuEventsHandler.hpp>
#include <event/management/handler/AuthorizationMenuEventsHandler.hpp>
#include <event/management/handler/GameRunnerEventsHandler.hpp>
#include <event/management/handler/WindowCloseHandler.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <event/system/KeyHeld.hpp>
#include <loader/LevelLoader.hpp>
#include <menu/MainMenu.hpp>
#include <menu/PauseMenu.hpp>
#include <runner/GameRunner.hpp>
#include <visual/Camera.hpp>
#include <world/LocalWorld.hpp>
#include <world/entity/ViewableEntity.hpp>

#include "event/management/controller/statemachine/StateMachine.hpp"
#include "event/management/condition/TrueCondition.hpp"
#include "event/system/KeyPressed.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <spdlog/spdlog.h>


class ArrowController : public mad::core::EventHandler {
public:
    explicit ArrowController(std::shared_ptr<mad::core::World> world,
                             mad::core::Entity::Id entity_id)
        : m_world(std::move(world)),
          m_entity_id(entity_id) {}

    void handle(const mad::core::Event &event) override {
        SPDLOG_INFO("handle arrow event");

        auto make_move_intent = [](mad::core::Vec2d dir) {
            return mad::core::LambdaIntent(
                    [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                        mad::core::cast_to<mad::core::ViewableEntity>(entity).move(dir);
                    });
        };

        auto impulse = [](mad::core::Vec2d dir) {
            return mad::core::LambdaIntent(
                    [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                        mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_linear_impulse_to_center(dir, event_dispatcher);
                    });
        };

        auto force = [](mad::core::Vec2d dir) {
            return mad::core::LambdaIntent(
                    [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                        mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_force_to_center(dir, event_dispatcher);
                    });
        };

        if (event.type == mad::core::Event::Type::KeyPressed) {
            const auto &keystroke = mad::core::const_cast_to<mad::core::KeyPressed>(event);
            if (keystroke.key_id == sf::Keyboard::Key::Space) {
                m_world->manipulate_entity_id(m_entity_id, impulse(mad::core::Vec2d{0.0f, -200000.0f}));
            }
        } else if (event.type == mad::core::Event::Type::KeyHeld) {
            const auto &keystroke = mad::core::const_cast_to<mad::core::KeyHeld>(event);
            if (keystroke.key_id == sf::Keyboard::Key::Right) {
                m_world->manipulate_entity_id(m_entity_id, force(mad::core::Vec2d{100000.0f, 0.0f}));
            }
            if (keystroke.key_id == sf::Keyboard::Key::Left) {
                m_world->manipulate_entity_id(m_entity_id, force(mad::core::Vec2d{-100000.0f, 0.0f}));
            }
        }
    }

    std::unordered_set<mad::core::Event::Type> handled_types() override {
        return {mad::core::Event::Type::KeyPressed, mad::core::Event::Type::KeyHeld};
    }

private:
    std::shared_ptr<mad::core::World> m_world;
    mad::core::Entity::Id m_entity_id;
};


class ExampleLevelLoader : public mad::core::LevelLoader {
public:
    std::unique_ptr<mad::core::LevelRunner> load(
            std::shared_ptr<mad::core::EventDispatcher> global_dispatcher,
            std::shared_ptr<mad::core::SystemListener> system_listener) override {
        auto level_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

        auto world = std::make_shared<mad::core::LocalWorld>(*level_dispatcher);

        auto camera = std::make_shared<mad::core::Camera>(mad::core::Vec2d{0.0f, 0.0f}, world);

        mad::core::Entity::Id square_id = world->create_viewable_entity(
                0,
                mad::core::Vec2d{0.0f, 0.0f},
                0,
                std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green()));

        mad::core::Entity::Id square_id_1 = world->create_physical_entity(
                0,
                mad::core::Vec2d{0.0f, 0.0f},
                0,
                std::make_shared<mad::core::StaticImage>("../../game/resources/static/brick.png", 50, 50,
                                                         mad::core::StaticImage::TransformType::Tile));

        mad::core::Entity::Id square_id_2 = world->create_physical_entity(
                0,
                mad::core::Vec2d{200.0f, 200.0f},
                0,
                std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green()),
                true);

        camera->turn_on(*level_dispatcher, square_id_1);
        level_dispatcher->registry(camera);
        level_dispatcher->registry(std::make_shared<ArrowController>(world, square_id_1));

        ///State Machine
        struct C1 : mad::core::Controller {
            void control() override {
                SPDLOG_DEBUG("controller 1");
            };
        };
        struct C2 : mad::core::Controller {
            void control() override {
                SPDLOG_DEBUG("controller 2");
            };
        };
        auto machine = std::make_shared<mad::core::StateMachine>(std::shared_ptr<mad::core::ImmediateDispatcher>(level_dispatcher));
        machine->add_state(std::make_shared<C1>());
        machine->add_state(std::make_shared<C2>());
        auto debug_1 = std::make_shared<mad::core::TrueCondition>(); //TODO
        auto debug2 = debug_1->triggers();
        machine->add_transition(0, 1, debug_1);
        //machine->add_transition(1, 0, std::make_shared<mad::core::TrueCondition>());
        machine->set_initial_state(0);
        std::vector<std::shared_ptr<mad::core::Controller>> v{machine};

        auto level_runner = std::make_unique<mad::core::LevelRunner>(
                system_listener,
                std::make_unique<mad::core::PauseMenu>(),
                camera,
                global_dispatcher,
                level_dispatcher,
                world,
                v);

        level_dispatcher->registry(std::make_shared<mad::core::LevelRunnerEventsHandler>(*level_runner));
        level_dispatcher->registry(std::make_shared<mad::core::PauseMenuEventsHandler>(*level_runner));

        return level_runner;
    }
};

// Comment for commit
int main() {
#ifndef NDEBUG
    auto log_level = spdlog::level::trace;
#else
    auto log_level = spdlog::level::info;
#endif
    spdlog::set_level(log_level);

    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "MAD");
    ImGui::SFML::Init(*window);
    window->setFramerateLimit(60);

    auto global_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

    auto system_listener = std::make_shared<mad::core::SystemListener>(window);

    auto offline_storage_driver = std::make_shared<mad::core::OfflineClientStorageDriver>();

    std::vector<std::shared_ptr<mad::core::LevelLoader>> level_loaders{
            std::make_shared<ExampleLevelLoader>()};


    auto game_runner = std::make_unique<mad::core::GameRunner>(
            level_loaders,
            global_dispatcher,
            std::make_unique<mad::core::MainMenu>(),
            std::make_unique<mad::core::AuthorizationMenu>(offline_storage_driver),
            system_listener,
            offline_storage_driver
    );

    global_dispatcher->registry(std::make_shared<mad::core::WindowCloseHandler>(*window));
    global_dispatcher->registry(std::make_shared<mad::core::MainMenuEventsHandler>(*game_runner));
    global_dispatcher->registry(std::make_shared<mad::core::GameRunnerEventsHandler>(*game_runner));
    global_dispatcher->registry(std::make_shared<mad::core::AuthorizationMenuEventsHandler>(*game_runner));

    game_runner->run(*window);

    ImGui::SFML::Shutdown();
}