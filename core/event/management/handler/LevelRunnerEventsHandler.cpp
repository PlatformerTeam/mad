#include "LevelRunnerEventsHandler.hpp"

#include <event/runner/LevelRunnerEvent.hpp>
#include <event/physics/Collision.hpp>
#include <event/system/KeyHeld.hpp>
#include <event/system/KeyPressed.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    LevelRunnerEventsHandler::LevelRunnerEventsHandler(LevelRunner &runner, std::shared_ptr<Condition> finish_condition) : m_runner(runner), m_finish_condition(std::move(finish_condition)) { }

    void LevelRunnerEventsHandler::handle(const Event &event) {
        //SPDLOG_DEBUG("Handle level runner event");

        if (event.type == Event::Type::KeyPressed) {
            const auto &keystroke = const_cast_to<KeyPressed>(event);
            if (keystroke.key_id == sf::Keyboard::Key::Escape) {
                m_runner.pause();
            }
        } else if (event.type == Event::Type::KeyHeld) {
            const auto &keystroke = const_cast_to<KeyHeld>(event);
            if (keystroke.key_id == sf::Keyboard::Key::Escape) {
                m_runner.pause();
            }
        } else if (event.type == Event::Type::Runner) {
            const auto &runner_event = const_cast_to<RunnerEvent>(event);
            if (runner_event.type == RunnerEvent::Type::LevelRunner) {
                const auto &level_runner_event = const_cast_to<LevelRunnerEvent>(runner_event);
                if (level_runner_event.level_runner_event_type == LevelRunnerEvent::Type::LevelStop) {
                    m_runner.stop();
                } else if (level_runner_event.level_runner_event_type == LevelRunnerEvent::Type::ApplicationFinish) {
                    m_runner.stop_and_exit();
                }
            }
        }
        if (m_finish_condition->triggers().count(event.type)) {
            if (event.type == Event::Type::Collision) {
                const auto &finisher_event = const_cast_to<Collision>(event);
                if (m_finish_condition->is_triggered_by(finisher_event)) {
                    m_runner.stop();
                }
            }
        }
    }

    std::unordered_set<Event::Type> LevelRunnerEventsHandler::handled_types() {
        std::unordered_set<Event::Type> runner_types{Event::Type::KeyPressed, Event::Type::KeyHeld, Event::Type::Runner};
        std::unordered_set<Event::Type> condition_types = m_finish_condition->triggers();
        for (const auto &c : condition_types) {
            runner_types.insert(c);
        }
        return runner_types;
    }
}