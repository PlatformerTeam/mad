#include "StateMachine.hpp"
#include "event/management/condition/Condition.hpp"
#include "event/management/condition/TrueCondition.hpp"
#include "spdlog/spdlog.h"

#include <utility>


std::unordered_set<mad::core::Event::Type> mad::core::Transition::handled_types() {
    return m_conditions[0]->triggers();
}
void mad::core::Transition::handle(const mad::core::Event &event) {
    if (!is_active || m_state_machine->has_made_transition) return;
    bool flag = true;
    for(auto &i : m_conditions){
        if(!i->is_triggered_by(event)){
            flag = false;
        }
    }
    if (flag) {
        m_state_machine->has_made_transition = true;
        m_state_machine->m_previous_state_id = m_state_machine->m_current_state_id;
        m_state_machine->m_current_state_id = next_state;
        SPDLOG_DEBUG("current state {}", m_state_machine->m_current_state_id);
        for (auto &i : m_state_machine->m_transitions[current_state]) {
            i->is_active = false;
        }
        for (auto &i : m_state_machine->m_transitions[next_state]) {
            i->is_active = true;
            for(auto &el : i->m_conditions){
                el->on_start();
            }
        }
    }
}
mad::core::Transition::Transition(mad::core::StateMachine *m_state_machine, mad::core::StateMachine::StateId current_state, mad::core::StateMachine::StateId next_state, std::shared_ptr<Condition> m_condition) : m_state_machine(m_state_machine), current_state(current_state), next_state(next_state), m_conditions({std::move(m_condition)}) {
}
mad::core::Transition::Transition(mad::core::StateMachine *m_state_machine, mad::core::StateMachine::StateId current_state, mad::core::StateMachine::StateId next_state, std::vector<std::shared_ptr<Condition>> m_conditions) : m_state_machine(m_state_machine), current_state(current_state), next_state(next_state), m_conditions(m_conditions)   {
}


/// StateMachine
void mad::core::StateMachine::control() {
    //SPDLOG_DEBUG("current state {}", m_current_state_id);
    has_made_transition = false;
    m_states[m_current_state_id]->control();
}
mad::core::StateMachine::StateId mad::core::StateMachine::add_state(const std::shared_ptr<Controller> &state) {
    m_states.push_back(state);
    m_transitions.emplace_back();
    return static_cast<StateId>(m_states.size()) - 1;
}
void mad::core::StateMachine::set_initial_state(mad::core::StateMachine::StateId state_id) {
    m_current_state_id = state_id;
    m_previous_state_id = state_id;
    for (auto &i : m_transitions[state_id]) {
        i->is_active = true;
    }
}
void mad::core::StateMachine::add_transition(mad::core::StateMachine::StateId state_id_from, mad::core::StateMachine::StateId state_id_to, std::shared_ptr<Condition> transition_condition) {
    auto transition = std::make_shared<Transition>(this, state_id_from, state_id_to, transition_condition);
    m_transitions[state_id_from].push_back(transition);
    m_dispatcher->registry(transition);
}
mad::core::StateMachine::StateMachine(std::shared_ptr<mad::core::ImmediateDispatcher> m_dispatcher) : m_dispatcher(std::move(m_dispatcher)){
}
mad::core::StateMachine::StateId mad::core::StateMachine::get_previous_state_id() {
    return m_previous_state_id;
}
