#ifndef MAD_STATEMACHINE_HPP
#define MAD_STATEMACHINE_HPP


#include <event/Event.hpp>
#include <event/management/controller/Controller.hpp>
#include <event/management/controller/statemachine/Condition/Condition.hpp>
namespace mad::core {
    struct Transition;
    struct StateMachine;


    struct StateMachine : Controller {
    public:
        using StateId = std::int32_t;
        StateId add_state(const std::shared_ptr<Controller> &state);
        void add_transition(StateId state_id_from, StateId state_id_to, std::shared_ptr<Condition> transition_condition);
        void set_initial_state(StateId state_id);
        void control() override;

    private:
        StateId m_current_state_id = -1;
        std::vector<std::shared_ptr<Controller>> m_states;
        std::vector<StateId, std::vector<Transition>> m_transitions;
    };


    struct Transition : EventHandler {
    public:
        std::unordered_set<Event::Type> handled_types() override;
        void handle(const Event &event) override;

    private:
        StateMachine::StateId next_state;
        std::shared_ptr<Condition> m_condition;
    };


}// namespace mad::core

#endif//MAD_STATEMACHINE_HPP
