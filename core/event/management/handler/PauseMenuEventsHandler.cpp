#include "PauseMenuEventsHandler.hpp"

#include <common/Cast.hpp>
#include <event/menu/MenuEvent.hpp>
#include <event/menu/PauseMenuEvent.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    PauseMenuEventsHandler::PauseMenuEventsHandler(LevelRunner &runner) : m_runner(runner) { }

    void PauseMenuEventsHandler::handle(const Event &event) {
        SPDLOG_INFO("handle pause menu event");

        if (event.type == Event::Type::Menu) {
            const auto &menu_event = const_cast_to<MenuEvent>(event);
            if (menu_event.type == MenuEvent::Type::PauseMenu) {
                const auto &pause_menu_event = const_cast_to<PauseMenuEvent>(event);
                if (pause_menu_event.type == PauseMenuEvent::Type::Continue) {
                    m_runner.resume();
                } else if (pause_menu_event.type == PauseMenuEvent::Type::ToMainMenu) {
                    m_runner.stop();
                }
            }
        }
    }

    std::unordered_set<Event::Type> PauseMenuEventsHandler::handled_types() {
        return {Event::Type::Menu};
    }


}