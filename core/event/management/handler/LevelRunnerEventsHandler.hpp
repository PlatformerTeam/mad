#ifndef MAD_LEVELRUNNEREVENTSHANDLER_HPP
#define MAD_LEVELRUNNEREVENTSHANDLER_HPP

#include <event/management/handler/EventHandler.hpp>
#include <runner/LevelRunner.hpp>

#include <unordered_set>


namespace mad::core {

    class LevelRunnerEventsHandler : public EventHandler {
    public:
        explicit LevelRunnerEventsHandler(LevelRunner& runner);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        LevelRunner& m_runner;
    };

}

#endif //MAD_LEVELRUNNEREVENTSHANDLER_HPP
