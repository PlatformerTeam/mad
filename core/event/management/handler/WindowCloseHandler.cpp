#include "WindowCloseHandler.hpp"


namespace mad::core {

    WindowCloseHandler::WindowCloseHandler(std::shared_ptr<SequentialRunner> runner,
                                           std::shared_ptr<sf::RenderWindow> window) : m_runner(std::move(runner)),
                                                                                     m_window(std::move(window)) {}

    void WindowCloseHandler::handle(const Event &event) {
        SPDLOG_INFO("handle window closing event");

        if (event.type == Event::Type::WindowClose) {
            m_window->close();
            m_runner->stop();
        }
    }

    std::unordered_set<Event::Type> WindowCloseHandler::handled_types() {
        return {Event::Type::WindowClose};
    }

}
