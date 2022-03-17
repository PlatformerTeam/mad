#include "SystemListener.hpp"

#include <spdlog/spdlog.h>

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/system/KeyPressed.hpp>
#include <event/system/KeyReleased.hpp>
#include <event/system/KeyHeld.hpp>


namespace mad::core {

    SystemListener::SystemListener(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {
        for (const auto &key : m_candidate_held_keys) {
            m_key_is_free[key] = true;
        }
    }

    void SystemListener::produce(EventDispatcher &dispatcher) {
        sf::Event ev{};
        m_window->pollEvent(ev);

        // Listen a keyboard
        if (ev.type == sf::Event::KeyPressed) {
            if (m_key_is_free[ev.key.code]) {
                dispatcher.dispatch(std::make_shared<KeyPressed>(ev.key.code));
            }
            m_key_is_free[ev.key.code] = false;
        } else if (ev.type == sf::Event::KeyReleased) {
            dispatcher.dispatch(std::make_shared<KeyReleased>(ev.key.code));
            m_key_is_free[ev.key.code] = true;
        }

        // Check held keys
        for (const auto &key : m_candidate_held_keys) {
            if (sf::Keyboard::isKeyPressed(key)) {
                dispatcher.dispatch(std::make_shared<KeyHeld>(key));
            }
        }
    }

}
