#include "GameRunnerEventsHandler.hpp"

#include <event/runner/GameRunnerEvent.hpp>


namespace mad::core {

    GameRunnerEventsHandler::GameRunnerEventsHandler(GameRunner &runner) : m_runner(runner) { }
//    GameRunnerEventsHandler::GameRunnerEventsHandler(GameRunner &runner, std::shared_ptr<DatabaseClientStorageDriver> db_driver) : m_runner(runner), m_db_driver(std::move(db_driver)) { }

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
                } else if (game_runner_event.game_runner_event_type == GameRunnerEvent::Type::UpdateProgress) {
                    // TODO m_db_driver->update_progress(...)
                }
            }
        }
    }

    std::unordered_set<Event::Type> GameRunnerEventsHandler::handled_types() {
        return {Event::Type::Runner};
    }


}