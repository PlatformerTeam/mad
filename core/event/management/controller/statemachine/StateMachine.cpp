#include "StateMachine.hpp"


std::unordered_set<mad::core::Event::Type> mad::core::Transition::handled_types() {
    return m_condition->triggers();
}
void mad::core::Transition::handle(const mad::core::Event &event) {
    if (m_condition->is_triggered_by(event)) {
        //change current state
    }
}
void mad::core::StateMachine::control() {
    m_states[m_current_state_id]->control();
}
mad::core::StateMachine::StateId mad::core::StateMachine::add_state(const std::shared_ptr<Controller> &state) {
    m_states.push_back(state);
    return (StateId) m_states.size() - 1;
}
void mad::core::StateMachine::set_initial_state(mad::core::StateMachine::StateId state_id) {
    m_current_state_id = state_id;
}
