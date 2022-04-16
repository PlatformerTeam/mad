#ifndef MAD_LEVELPAUSEHANDLER_HPP
#define MAD_LEVELPAUSEHANDLER_HPP

#include <event/management/handler/EventHandler.hpp>
#include <runner/LevelRunner.hpp>

#include <spdlog/spdlog.h>
#include <unordered_set>


namespace mad::core {

    class LevelPauseHandler : public EventHandler {
    public:
        explicit LevelPauseHandler(LevelRunner& runner);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        LevelRunner& m_runner;
    };

}

#endif//MAD_LEVELPAUSEHANDLER_HPP
