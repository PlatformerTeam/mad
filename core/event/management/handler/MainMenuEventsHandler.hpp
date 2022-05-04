#ifndef MAD_MAINMENUEVENTSHANDLER_HPP
#define MAD_MAINMENUEVENTSHANDLER_HPP

#include <event/management/handler/EventHandler.hpp>
#include <runner/GameRunner.hpp>

#include <spdlog/spdlog.h>

#include <unordered_set>


namespace mad::core {

    class MainMenuEventsHandler : public EventHandler {
    public:
        explicit MainMenuEventsHandler(GameRunner& runner);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        GameRunner& m_runner;
    };

}

#endif //MAD_CLOSINGHANDLER_HPP
