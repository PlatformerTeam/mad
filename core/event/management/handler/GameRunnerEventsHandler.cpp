#include "GameRunnerEventsHandler.hpp"

#include <event/system/ApplicationFinish.hpp>


namespace mad::core {

    GameRunnerEventsHandler::GameRunnerEventsHandler(GameRunner &runner) : m_runner(runner) { }

    void GameRunnerEventsHandler::handle(const Event &event) {
        SPDLOG_DEBUG("Handle game runner event");

        if (event.type == Event::Type::ApplicationFinish) {
            m_runner.stop();
        }
    }

    std::unordered_set<Event::Type> GameRunnerEventsHandler::handled_types() {
        return {Event::Type::ApplicationFinish};
    }


}