#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/handler/LevelPauseHandler.hpp>
#include <event/management/handler/MainMenuEventsHandler.hpp>
#include <event/management/handler/WindowCloseHandler.hpp>
#include <event/management/handler/PauseMenuEventsHandler.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <event/system/KeyHeld.hpp>
#include <event/system/KeyPressed.hpp>
#include <loader/LevelLoader.hpp>
#include <menu/MainMenu.hpp>
#include <menu/PauseMenu.hpp>
#include <runner/GameRunner.hpp>
#include <visual/Camera.hpp>
#include <world/LocalWorld.hpp>
#include <world/entity/ViewableEntity.hpp>

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
        SPDLOG_DEBUG("handle arrow event");

        auto make_move_intent = [](mad::core::Vec2d dir) {
            return mad::core::LambdaIntent(
                    [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                        mad::core::cast_to<mad::core::ViewableEntity>(entity).move(dir);
                    });
        };

//        if (event.type == mad::core::Event::Type::KeyPressed) {
//            const auto &keystroke = mad::core::const_cast_to<mad::core::KeyPressed>(event);
//            if (keystroke.key_id == sf::Keyboard::Key::Up) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, -10.0f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Down) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, 10.0f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Left) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{-10.0f, 0.0f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Right) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{10.0f, 0.0f}));
//            }
//        } else
        if (event.type == mad::core::Event::Type::KeyHeld) {
            const auto &keystroke = mad::core::const_cast_to<mad::core::KeyHeld>(event);
            if (keystroke.key_id == sf::Keyboard::Key::Up) {
                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, -1.f}));
            } else if (keystroke.key_id == sf::Keyboard::Key::Down) {
                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, 1.f}));
            } else if (keystroke.key_id == sf::Keyboard::Key::Left) {
                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{-1.f, 0.0f}));
            } else if (keystroke.key_id == sf::Keyboard::Key::Right) {
                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{1.f, 0.0f}));
            }
        }
    }

    std::unordered_set<mad::core::Event::Type> handled_types() override {
        return {mad::core::Event::Type::KeyHeld};
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
                std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green())
        );

        camera->turn_on(*level_dispatcher);
        level_dispatcher->registry(camera);
        level_dispatcher->registry(std::make_shared<ArrowController>(world, square_id));

        auto level_runner = std::make_unique<mad::core::LevelRunner>(
                system_listener,
                std::make_unique<mad::core::PauseMenu>(),
                camera,
                global_dispatcher,
                level_dispatcher,
                world
        );

        level_dispatcher->registry(std::make_shared<mad::core::LevelPauseHandler>(*level_runner));
        level_dispatcher->registry(std::make_shared<mad::core::PauseMenuEventsHandler>(*level_runner));

        return level_runner;
    }
};

int main() {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "MAD");
    ImGui::SFML::Init(*window);
    window->setFramerateLimit(60);

    auto global_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

    auto system_listener = std::make_shared<mad::core::SystemListener>(window);

    std::vector<std::shared_ptr<mad::core::LevelLoader>> level_loaders {
            std::make_shared<ExampleLevelLoader>()
    };

    auto game_runner = std::make_unique<mad::core::GameRunner>(
            level_loaders,
            global_dispatcher,
            std::make_unique<mad::core::MainMenu>(),
            system_listener
    );

    global_dispatcher->registry(std::make_shared<mad::core::WindowCloseHandler>(*game_runner, *window));
    global_dispatcher->registry(std::make_shared<mad::core::MainMenuEventsHandler>(*game_runner));

    game_runner->run(*window);

    ImGui::SFML::Shutdown();
}