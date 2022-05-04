#ifndef MAD_GAMERUNNEREVENTSHANDLER_HPP
#define MAD_GAMERUNNEREVENTSHANDLER_HPP

#include <event/management/handler/EventHandler.hpp>
#include <runner/GameRunner.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    class GameRunnerEventsHandler : public EventHandler {
    public:
        explicit GameRunnerEventsHandler(GameRunner& runner);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        GameRunner& m_runner;
    };

}

#endif //MAD_GAMERUNNEREVENTSHANDLER_HPP
