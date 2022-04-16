#include "SystemListener.hpp"

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/system/KeyPressed.hpp>
#include <event/system/KeyReleased.hpp>
#include <event/system/KeyHeld.hpp>
#include <event/system/WindowClose.hpp>

#include <imgui-SFML.h>
#include <spdlog/spdlog.h>


namespace mad::core {

    SystemListener::SystemListener(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {}

    void SystemListener::produce(EventDispatcher &dispatcher) {
        sf::Event ev{sf::Event::KeyPressed};
        m_window->pollEvent(ev);

        // Listen a window
        if (ev.type == sf::Event::Closed) {
            dispatcher.dispatch(std::make_shared<WindowClose>());
        }
        // Listen a keyboard
        else if (ev.type == sf::Event::KeyPressed) {
            if (m_key_held.find(ev.key.code) == m_key_held.end()) {
                dispatcher.dispatch(std::make_shared<KeyPressed>(ev.key.code));
                m_key_held.insert(ev.key.code);
            }
        } else if (ev.type == sf::Event::KeyReleased) {
            dispatcher.dispatch(std::make_shared<KeyReleased>(ev.key.code));
            m_key_held.erase(ev.key.code);
        }
        // Process ImGui
        else {
            ImGui::SFML::ProcessEvent(ev);
        }

        // Check held keys
        for (const auto &key : m_key_held) {
            if (sf::Keyboard::isKeyPressed(key)) {
                dispatcher.dispatch(std::make_shared<KeyHeld>(key));
            }
        }
    }

}
