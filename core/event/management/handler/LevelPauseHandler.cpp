#include "LevelPauseHandler.hpp"


namespace mad::core {

    LevelPauseHandler::LevelPauseHandler(std::shared_ptr<LevelRunner> runner) : m_runner(std::move(runner)) { }

    void LevelPauseHandler::handle(const Event &event) {
        SPDLOG_INFO("handle level pause event");

        if (event.type == Event::Type::LevelPause) {
            m_runner->pause();
        }
    }

    std::unordered_set<Event::Type> LevelPauseHandler::handled_types() {
        return {Event::Type::LevelPause};
    }

}
