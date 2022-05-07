#include "AuthorizationMenuEventsHandler.hpp"

#include <common/Cast.hpp>
#include <event/menu/MenuEvent.hpp>
#include <event/menu/AuthorizationMenuEvent.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    AuthorizationMenuEventsHandler::AuthorizationMenuEventsHandler(GameRunner &runner) : m_runner(runner) { }

    void AuthorizationMenuEventsHandler::handle(const Event &event) {
        SPDLOG_DEBUG("Handle auth menu event");

        if (event.type == Event::Type::Menu) {
            const auto &menu_event = const_cast_to<MenuEvent>(event);
            if (menu_event.type == MenuEvent::Type::AuthorizationMenu) {
                const auto &auth_menu_event = const_cast_to<AuthorizationMenuEvent>(event);
                if (auth_menu_event.auth_menu_type == AuthorizationMenuEvent::Type::Enter) {
                    m_runner.to_main_menu();
                }
            }
        }
    }

    std::unordered_set<Event::Type> AuthorizationMenuEventsHandler::handled_types() {
        return {Event::Type::Menu};
    }

}
