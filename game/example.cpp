#include <event/management/EventProducer.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/system/Keystroke.hpp>
#include <runner/SequentialRunner.hpp>
#include <system/SystemListener.hpp>
#include <world/LocalWorld.hpp>
#include <world/entity/ViewableEntity.hpp>
#include <visual/Camera.hpp>

#include <spdlog/spdlog.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


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

        if (event.type == mad::core::Event::Type::Keystroke) {
            const auto &keystroke = mad::core::const_cast_to<mad::core::Keystroke>(event);
            if (keystroke.key_id == sf::Keyboard::Key::Up) {
                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, 1.0f}));
            } else if (keystroke.key_id == sf::Keyboard::Key::Down) {
                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, -1.0f}));
            } else if (keystroke.key_id == sf::Keyboard::Key::Left) {
                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{-1.0f, 0.0f}));
            } else if (keystroke.key_id == sf::Keyboard::Key::Right) {
                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{1.0f, 0.0f}));
            }
        }
    }

    std::unordered_set<mad::core::Event::Type> handled_types() override {
        return {mad::core::Event::Type::Keystroke};
    }

private:
    std::shared_ptr<mad::core::World> m_world;
    mad::core::Entity::Id m_entity_id;
};


int main(int argc, char *argv[]) {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "MAD");

    auto system_listener = std::make_shared<mad::core::SystemListener>(window);

    auto world = std::make_shared<mad::core::LocalWorld>();

    auto camera = std::make_shared<mad::core::Camera>(mad::core::Vec2d{0.0f, 0.0f}, world);

    mad::core::Entity::Id square_id = world->create_viewable_entity(
            0,
            mad::core::Vec2d{0.0f, 0.0f},
            std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green())
    );

    mad::core::Entity::Id static_id = world->create_viewable_entity(
            0,
            mad::core::Vec2d{0.0f, 0.0f},
            std::make_shared<mad::core::StaticImage>("../../game/resources/18plus.png",
                                                     mad::core::Vec2d(0.5, 0.9),
                                                     sf::IntRect{0, 0, 200, 300})
    );

    auto dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

    camera->turn_on(*dispatcher);

    dispatcher->registry(camera);
    dispatcher->registry(std::make_shared<ArrowController>(world, square_id));

    mad::core::SequentialRunner runner(std::vector<std::shared_ptr<mad::core::EventProducer>>{system_listener, world},
                                       std::vector<std::shared_ptr<mad::core::Renderable>>{camera},
                                       dispatcher);

    runner.run(*window);
}
