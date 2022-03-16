#include "SystemListener.hpp"

#include <spdlog/spdlog.h>

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/system/KeyPressed.hpp>


namespace mad::core {

    SystemListener::SystemListener(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {}

    void SystemListener::produce(EventDispatcher &dispatcher) {
        sf::Event ev{};
        m_window->pollEvent(ev);

        // Listen a keyboard
        if (ev.type == sf::Event::KeyPressed) {
            dispatcher.dispatch(std::make_shared<KeyPressed>(ev.key.code));
        }

        // ...
    }

}
