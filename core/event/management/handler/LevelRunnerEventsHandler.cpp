#include "LevelRunnerEventsHandler.hpp"

#include <event/system/ApplicationFinish.hpp>
#include <event/system/KeyHeld.hpp>
#include <event/system/KeyPressed.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    LevelRunnerEventsHandler::LevelRunnerEventsHandler(LevelRunner &runner) : m_runner(runner) { }

    void LevelRunnerEventsHandler::handle(const Event &event) {
        SPDLOG_DEBUG("Handle level runner event");

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
        } else if (event.type == Event::Type::ApplicationFinish) {
            m_runner.stop();
        }
    }

    std::unordered_set<Event::Type> LevelRunnerEventsHandler::handled_types() {
        return {Event::Type::KeyPressed, Event::Type::KeyHeld, Event::Type::ApplicationFinish};
    }
}