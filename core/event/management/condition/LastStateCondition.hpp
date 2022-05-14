#ifndef MAD_LASTSTATECONDITION_HPP
#define MAD_LASTSTATECONDITION_HPP

#include "Condition.hpp"
#include "event/management/controller/statemachine/StateMachine.hpp"
namespace mad::core {
    struct LastStateCondition : Condition {
    public:
        LastStateCondition(std::shared_ptr<StateMachine> m_machine, StateMachine::StateId m_to_state_id);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        std::shared_ptr<StateMachine> m_machine;
        StateMachine::StateId m_to_state_id;
    };
}// namespace mad::core

#endif//MAD_LASTSTATECONDITION_HPP
