#include <event/management/EventProducer.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/Event.hpp>
#include <runner/SequentialRunner.hpp>
#include <common/Error.hpp>
#include <system/SystemListener.hpp>
#include <world/LocalWorld.hpp>
#include <visual/Camera.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>


int main(int argc, char *argv[]) {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "MAD");

    auto system_listener = std::make_shared<mad::core::SystemListener>(window);

    auto world = std::make_shared<mad::core::LocalWorld>();

    auto camera = std::make_shared<mad::core::Camera>(mad::core::Vec2d{0.0f, 0.0f}, world);

    world->create_viewable_entity(0, mad::core::Vec2d{0.0f, 0.0f},
                                  std::make_shared<mad::core::Square>(50.0f, mad::core::Color::Green()));

    mad::core::SequentialRunner runner(std::vector<std::shared_ptr<mad::core::EventProducer>>{system_listener, world},
                                       std::vector<std::shared_ptr<mad::core::Renderable>>{camera},
                                       std::make_shared<mad::core::ImmediateDispatcher>(),
                                       camera);

    runner.run(*window);
}
