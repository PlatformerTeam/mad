#include "MainMenuEventsHandler.hpp"

#include <common/Cast.hpp>
#include <event/menu/MenuEvent.hpp>
#include <event/menu/MainMenuEvent.hpp>


namespace mad::core {

    MainMenuEventsHandler::MainMenuEventsHandler(GameRunner &runner) : m_runner(runner) { }

    void MainMenuEventsHandler::handle(const Event &event) {
        SPDLOG_DEBUG("Handle main menu event");

        if (event.type == Event::Type::Menu) {
            const auto &menu_event = const_cast_to<MenuEvent>(event);
            if (menu_event.type == MenuEvent::Type::MainMenu) {
                const auto &main_menu_event = const_cast_to<MainMenuEvent>(event);
                if (main_menu_event.main_menu_event_type == MainMenuEvent::Type::NewGame) {
                    m_runner.start_game();
                } else if (main_menu_event.main_menu_event_type == MainMenuEvent::Type::Quit) {
                    m_runner.stop();
                }
            }
        }
    }

    std::unordered_set<Event::Type> MainMenuEventsHandler::handled_types() {
        return {Event::Type::Menu};
    }

}
