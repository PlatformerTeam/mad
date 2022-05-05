#include "StateMachine.hpp"
#include "spdlog/spdlog.h"

#include <utility>


std::unordered_set<mad::core::Event::Type> mad::core::Transition::handled_types() {
    return m_condition->triggers();
}
void mad::core::Transition::handle(const mad::core::Event &event) {
    if (m_condition->is_triggered_by(event)) {
        m_state_machine->m_current_state_id = next_state;
    }
}
mad::core::Transition::Transition(mad::core::StateMachine *m_state_machine, mad::core::StateMachine::StateId next_state, std::shared_ptr<Condition> m_condition) : m_state_machine(m_state_machine), next_state(next_state), m_condition(std::move(m_condition)) {
}


/// StateMachine
void mad::core::StateMachine::control() {
    SPDLOG_DEBUG("current state {}", m_current_state_id);
    m_states[m_current_state_id]->control();
}
mad::core::StateMachine::StateId mad::core::StateMachine::add_state(const std::shared_ptr<Controller> &state) {
    m_states.push_back(state);
    return static_cast<StateId>(m_states.size()) - 1;
}
void mad::core::StateMachine::set_initial_state(mad::core::StateMachine::StateId state_id) {
    m_current_state_id = state_id;
}
void mad::core::StateMachine::add_transition(mad::core::StateMachine::StateId state_id_from, mad::core::StateMachine::StateId state_id_to, std::shared_ptr<Condition> transition_condition) {
    auto transition = std::make_shared<Transition>(this, state_id_to, transition_condition);
    m_transitions[state_id_from].push_back(transition);
    m_dispatcher->registry(transition);
}