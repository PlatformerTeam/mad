#include "LevelPauseHandler.hpp"

#include <event/system/KeyPressed.hpp>
#include <event/system/KeyHeld.hpp>


namespace mad::core {

    LevelPauseHandler::LevelPauseHandler(LevelRunner& runner) : m_runner(runner) { }

    void LevelPauseHandler::handle(const Event &event) {
        SPDLOG_DEBUG("handle level pause event");

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
        }
    }

    std::unordered_set<Event::Type> LevelPauseHandler::handled_types() {
        return {Event::Type::KeyPressed, Event::Type::KeyHeld};
    }

}
