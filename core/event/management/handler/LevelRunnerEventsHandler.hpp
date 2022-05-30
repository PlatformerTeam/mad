#ifndef MAD_LEVELRUNNEREVENTSHANDLER_HPP
#define MAD_LEVELRUNNEREVENTSHANDLER_HPP

#include <event/management/condition/Condition.hpp>
#include <event/management/handler/EventHandler.hpp>
#include <runner/LevelRunner.hpp>

#include <unordered_set>


namespace mad::core {

    class LevelRunnerEventsHandler : public EventHandler {
    public:
        explicit LevelRunnerEventsHandler(LevelRunner& runner, std::shared_ptr<Condition> finish_condition);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        LevelRunner& m_runner;
        std::shared_ptr<Condition> m_finish_condition;
    };

}

#endif //MAD_LEVELRUNNEREVENTSHANDLER_HPP
