#include "GameRunnerEventsHandler.hpp"

#include <event/runner/GameRunnerEvent.hpp>


namespace mad::core {

    GameRunnerEventsHandler::GameRunnerEventsHandler(GameRunner &runner) : m_runner(runner) { }

    void GameRunnerEventsHandler::handle(const Event &event) {
        SPDLOG_DEBUG("Handle game runner event");

        if (event.type == Event::Type::Runner) {
            const auto &runner_event = const_cast_to<RunnerEvent>(event);
            if (runner_event.type == RunnerEvent::Type::GameRunner) {
                const auto &game_runner_event = const_cast_to<GameRunnerEvent>(runner_event);
                if (game_runner_event.game_runner_event_type == GameRunnerEvent::Type::ApplicationFinish) {
                    m_runner.stop();
                } else if (game_runner_event.game_runner_event_type == GameRunnerEvent::Type::GameStop) {
                    m_runner.to_main_menu();
                }
            }
        }
    }

    std::unordered_set<Event::Type> GameRunnerEventsHandler::handled_types() {
        return {Event::Type::Runner};
    }


}