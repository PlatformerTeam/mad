#include "WindowCloseHandler.hpp"

#include <common/Cast.hpp>
#include <event/menu/MenuEvent.hpp>
#include <event/menu/MainMenuEvent.hpp>


namespace mad::core {

    WindowCloseHandler::WindowCloseHandler(Runner& runner,
                                           sf::RenderWindow& window) : m_runner(runner),
                                                                                     m_window(window) {}

    void WindowCloseHandler::handle(const Event &event) {
        SPDLOG_DEBUG("handle window closing event");

        if (event.type == Event::Type::WindowClose) {
            m_window.close();
            m_runner.stop();
        } else if (event.type == Event::Type::Menu) {
            const auto &menu_event = const_cast_to<MenuEvent>(event);
            if (menu_event.type == MenuEvent::Type::MainMenu) {
                const auto &main_menu_event = const_cast_to<MainMenuEvent>(event);
                if (main_menu_event.type == MainMenuEvent::Type::Quit) {
                    m_window.close();
                    m_runner.stop();
                }
            }
        }
    }

    std::unordered_set<Event::Type> WindowCloseHandler::handled_types() {
        return {Event::Type::WindowClose, Event::Type::Menu};
    }

}
