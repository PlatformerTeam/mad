#include "WindowCloseHandler.hpp"

#include <event/system/WindowClose.hpp>


namespace mad::core {

    WindowCloseHandler::WindowCloseHandler(sf::RenderWindow& window) : m_window(window) {}

    void WindowCloseHandler::handle(const Event &event) {
        SPDLOG_DEBUG("handle window closing event");

        if (event.type == Event::Type::WindowClose) {
            m_window.close();
        }
    }

    std::unordered_set<Event::Type> WindowCloseHandler::handled_types() {
        return {Event::Type::WindowClose};
    }

}
