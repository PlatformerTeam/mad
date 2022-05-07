#include "AuthorizationMenuEventsHandler.hpp"

#include <event/Event.hpp>


namespace mad::core {

    AuthorizationMenuEventsHandler::AuthorizationMenuEventsHandler(GameRunner &runner) : m_runner(runner) { }

    void AuthorizationMenuEventsHandler::handle(const Event &event) {

    }

    std::unordered_set<Event::Type> AuthorizationMenuEventsHandler::handled_types() {
        return {Event::Type::Menu};
    }

}
