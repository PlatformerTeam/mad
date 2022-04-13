#include "LevelPauseHandler.hpp"

#include <event/system/KeyPressed.hpp>


namespace mad::core {

    LevelPauseHandler::LevelPauseHandler(std::shared_ptr<LevelRunner> runner) : m_runner(std::move(runner)) { }

    void LevelPauseHandler::handle(const Event &event) {
        SPDLOG_INFO("handle level pause event");

//        if (event.type == Event::Type::LevelPause) {
//            m_runner->pause();
//        }

        if (event.type == Event::Type::KeyPressed) {
            const auto &keystroke = const_cast_to<KeyPressed>(event);
            if (keystroke.key_id == sf::Keyboard::Key::Escape) {
                m_runner->pause();
            }
        }
    }

    std::unordered_set<Event::Type> LevelPauseHandler::handled_types() {
        //return {Event::Type::LevelPause};
        return {Event::Type::KeyPressed};
    }

}
