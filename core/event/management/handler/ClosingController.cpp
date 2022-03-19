#include "ClosingController.hpp"


namespace mad::core {

    ClosingController::ClosingController(std::shared_ptr<SequentialRunner> runner,
                                         std::shared_ptr<sf::RenderWindow> window) : m_runner(std::move(runner)),
                                                                                     m_window(std::move(window)) {}

    void ClosingController::handle(const Event &event) {
        SPDLOG_INFO("handle window closing event");

        if (event.type == Event::Type::WindowClosed) {
            m_window->close();
            m_runner->stop();
        }
    }

    std::unordered_set<Event::Type> ClosingController::handled_types() {
        return {Event::Type::WindowClosed};
    }

}
