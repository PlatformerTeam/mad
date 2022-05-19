#ifndef MAD_AUTHORIZATIONMENUEVENTSHANDLER_HPP
#define MAD_AUTHORIZATIONMENUEVENTSHANDLER_HPP

#include <event/management/handler/EventHandler.hpp>
#include <runner/GameRunner.hpp>

#include <unordered_set>


namespace mad::core {

    class AuthorizationMenuEventsHandler : public EventHandler {
    public:
        explicit AuthorizationMenuEventsHandler(GameRunner& runner);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        GameRunner& m_runner;
    };

}


#endif //MAD_AUTHORIZATIONMENUEVENTSHANDLER_HPP
