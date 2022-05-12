#ifndef MAD_STATEMACHINE_HPP
#define MAD_STATEMACHINE_HPP


#include "event/management/dispatcher/ImmediateDispatcher.hpp"
#include <event/Event.hpp>
#include <event/management/controller/Controller.hpp>
#include <event/management/condition/Condition.hpp>
namespace mad::core {
    struct StateMachine;
    struct Transition;


    struct StateMachine : Controller {
    public:
        using StateId = std::int32_t;

        explicit StateMachine(std::shared_ptr<mad::core::ImmediateDispatcher> m_dispatcher);

        StateId add_state(const std::shared_ptr<Controller> &state);
        void add_transition(StateId state_id_from, StateId state_id_to, std::shared_ptr<Condition> transition_condition);
        void set_initial_state(StateId state_id);
        void control() override;

    private:
        StateId m_current_state_id = -1;
        std::vector<std::shared_ptr<Controller>> m_states;
        std::vector<std::vector<std::shared_ptr<Transition>>> m_transitions;
        std::shared_ptr<mad::core::ImmediateDispatcher> m_dispatcher;
        bool has_made_transition = false;
        friend Transition;
    };

    struct Transition : EventHandler {
    public:
        Transition(StateMachine *m_state_machine, StateMachine::StateId current_state, StateMachine::StateId next_state, std::shared_ptr<Condition> m_condition);
        std::unordered_set<Event::Type> handled_types() override;
        void handle(const Event &event) override;
        bool is_active = false;

    private:
        StateMachine *m_state_machine;
        StateMachine::StateId current_state;
        StateMachine::StateId next_state;
        std::shared_ptr<Condition> m_condition;
    };

}// namespace mad::core

#endif//MAD_STATEMACHINE_HPP
