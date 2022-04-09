#include <event/management/producer/EventProducer.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/handler/WindowCloseHandler.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <event/system/KeyHeld.hpp>
#include <event/system/KeyPressed.hpp>
#include <runner/SequentialRunner.hpp>
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
                        mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_impulse(dir, event_dispatcher);
                    });
        };

        auto force = [](mad::core::Vec2d dir) {
            return mad::core::LambdaIntent(
                    [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                        mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_force(dir, event_dispatcher);
                    });
        };

        if (event.type == mad::core::Event::Type::KeyPressed) {
            const auto &keystroke = mad::core::const_cast_to<mad::core::KeyPressed>(event);
            if (keystroke.key_id == sf::Keyboard::Key::Space) {
                m_world->manipulate_entity_id(m_entity_id, impulse(mad::core::Vec2d{0.0f, 200000.0f}));
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

int main(int argc, char *argv[]) {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "MAD");

    auto system_listener = std::make_shared<mad::core::SystemListener>(window);

    auto world = std::make_shared<mad::core::LocalWorld>();

    auto camera = std::make_shared<mad::core::Camera>(mad::core::Vec2d{0.0f, 0.0f}, world);

    mad::core::Entity::Id square_id = world->create_viewable_entity(
            0,
            mad::core::Vec2d{25.0f, 25.0f},0,
            std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green())
    );

    mad::core::Entity::Id square_id1 = world->create_physical_entity(
            3,
            mad::core::Vec2d{100.0f, 25.0f},0,
            std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green())
    );

    mad::core::Entity::Id square_id2 = world->create_physical_entity(
            0,
            mad::core::Vec2d{80.0f, 100.0f},0.5,
            std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green()),
                    true
    );

    mad::core::Entity::Id square_id3 = world->create_physical_entity(
            0,
            mad::core::Vec2d{180.0f, 180.0f},-0.5,
            std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green()),
            true
    );

    mad::core::Entity::Id square_id4 = world->create_physical_entity(
            0,
            mad::core::Vec2d{80.0f, 260.0f},0.5,
            std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green()),
            true
    );

    mad::core::Entity::Id square_id5 = world->create_physical_entity(
            0,
            mad::core::Vec2d{180.0f, 340.0f},-0.5,
            std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green()),
            true
    );

    mad::core::Entity::Id square_id6 = world->create_physical_entity(
            0,
            mad::core::Vec2d{500.0f, 500.0f},0,
            std::make_shared<mad::core::Square>(500.0f, mad::core::Color::Green()),
            true
    );
    world->create_physical_entity(
            0,
            mad::core::Vec2d{800.0f, 0.0f},0,
            std::make_shared<mad::core::Square>(500.0f, mad::core::Color::Green()),
            true
    );

    for(int i = 0; i < 100; i++){
        world->create_physical_entity(
                0,
                mad::core::Vec2d{500 + (float)(rand() % 100), (float)(rand() % 100)},0,
                std::make_shared<mad::core::Square>(5.0f, mad::core::Color::Green())
        );
    }

    //mad::core::StaticImage st_im_1 = mad::core::StaticImage("../../game/resources/brick.png", 50, 50, mad::core::StaticImage::TransformType::Fit);
    mad::core::Entity::Id static_id_1 = world->create_viewable_entity(
            2,
            mad::core::Vec2d{180.0f, 340.0f},-0.5,
            std::make_shared<mad::core::StaticImage>(mad::core::StaticImage("../../game/resources/brick.png", 300.0f, 50.0f, mad::core::StaticImage::TransformType::Fit))
    );

    /*mad::core::StaticImage st_im_2 = mad::core::StaticImage("../../game/resources/18plus.png");
    st_im_2.set_shape(400, 400, mad::core::StaticImage::TransformType::Tile);
    mad::core::Entity::Id static_id_2 = world->create_viewable_entity(
            0,
            mad::core::Vec2d{100.0f, 20.0f},0,
            std::make_shared<mad::core::StaticImage>(st_im_2)
    );*/


    auto dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

    camera->turn_on(*dispatcher);

    dispatcher->registry(camera);
    dispatcher->registry(std::make_shared<ArrowController>(world, square_id1));

    auto runner = std::make_shared<mad::core::SequentialRunner>(std::vector<std::shared_ptr<mad::core::EventProducer>>{system_listener, world},
                                                                std::vector<std::shared_ptr<mad::core::Renderable>>{camera},
                                                                dispatcher);
    dispatcher->registry(std::make_shared<mad::core::WindowCloseHandler>(runner, window));

    runner->run(*window);
}
