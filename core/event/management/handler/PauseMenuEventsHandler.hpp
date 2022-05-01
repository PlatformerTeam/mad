#ifndef MAD_PAUSEMENUEVENTSHANDLER_HPP
#define MAD_PAUSEMENUEVENTSHANDLER_HPP

#include <event/management/handler/EventHandler.hpp>
#include <runner/LevelRunner.hpp>

#include <spdlog/spdlog.h>
#include <unordered_set>


namespace mad::core {

    class PauseMenuEventsHandler : public EventHandler {
    public:
        explicit PauseMenuEventsHandler(LevelRunner& runner);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        LevelRunner& m_runner;
    };

}

#endif //MAD_PAUSEMENUEVENTSHANDLER_HPP
