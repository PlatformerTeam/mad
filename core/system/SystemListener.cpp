#include "SystemListener.hpp"

#include <event/management/EventDispatcher.hpp>
#include <event/system/Keystroke.hpp>

namespace mad::core {

    SystemListener::SystemListener() = default;

    SystemListener::SystemListener(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {}

    void SystemListener::produce(EventDispatcher &dispatcher) {
        // Listen a keyboard
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::A)));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::D)));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::W)));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::S)));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::LShift)));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::Space)));
        }

        // ...
    }

}
