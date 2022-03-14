#include "SystemListener.hpp"

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/system/Keystroke.hpp>

namespace mad::core {

    SystemListener::SystemListener(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {}

    void SystemListener::produce(EventDispatcher &dispatcher) {
        sf::Event ev;
        m_window->pollEvent(ev);

        // Listen a keyboard
        if (ev.type == sf::Event::KeyPressed) {
            if (ev.key.code == sf::Keyboard::A) {
                dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::A)));
            }
            if (ev.key.code == sf::Keyboard::D) {
                dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::D)));
            }
            if (ev.key.code == sf::Keyboard::W) {
                dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::W)));
            }
            if (ev.key.code == sf::Keyboard::S) {
                dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::S)));
            }
            if (ev.key.code == sf::Keyboard::LShift) {
                dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::LShift)));
            }
            if (ev.key.code == sf::Keyboard::Space) {
                dispatcher.dispatch(std::make_shared<Keystroke>(Keystroke(sf::Keyboard::Key::Space)));
            }
        }

        // ...
    }

}
