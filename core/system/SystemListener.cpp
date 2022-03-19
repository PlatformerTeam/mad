#include "SystemListener.hpp"

#include <spdlog/spdlog.h>

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/system/KeyPressed.hpp>
#include <event/system/KeyReleased.hpp>
#include <event/system/KeyHeld.hpp>
#include <event/system/WindowClosing.hpp>

#include <string>


namespace mad::core {

    SystemListener::SystemListener(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {}

    void SystemListener::produce(EventDispatcher &dispatcher) {
        sf::Event ev{};
        m_window->pollEvent(ev);

//        if (ev.type == sf::Event::Closed) {
//            SPDLOG_INFO("catch close event");
//            endless :(
//        }

        // Listen a window
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Key::Escape) {
            SPDLOG_INFO("catch close event");
            dispatcher.dispatch(std::make_shared<WindowClosing>());
        }

        // Listen a keyboard
        if (ev.type == sf::Event::KeyPressed) {
            if (m_key_held.find(ev.key.code) == m_key_held.end()) {
                dispatcher.dispatch(std::make_shared<KeyPressed>(ev.key.code));
            }
            m_key_held.insert(ev.key.code);
        } else if (ev.type == sf::Event::KeyReleased) {
            dispatcher.dispatch(std::make_shared<KeyReleased>(ev.key.code));
            m_key_held.erase(ev.key.code);
        }

        // Check held keys
        for (const auto &key : m_key_held) {
            if (sf::Keyboard::isKeyPressed(key)) {
                dispatcher.dispatch(std::make_shared<KeyHeld>(key));
            }
        }
    }

}
