#include "LastStateCondition.hpp"

bool mad::core::LastStateCondition::is_triggered_by(const mad::core::Event &event) {
    return m_to_state_id == m_machine->get_previous_state_id();
}
std::unordered_set<mad::core::Event::Type> mad::core::LastStateCondition::triggers() {
    return {mad::core::Event::Type::KeyPressed, mad::core::Event::Type::Collision, mad::core::Event::Type::KeyHeld, mad::core::Event::Type::KeyReleased, mad::core::Event::Type::LevelPause, mad::core::Event::Type::Menu, mad::core::Event::Type::Movement, mad::core::Event::Type::Runner, mad::core::Event::Type::Visual, mad::core::Event::Type::WindowClose};
}
void mad::core::LastStateCondition::on_start() {
}
mad::core::LastStateCondition::LastStateCondition(std::shared_ptr<StateMachine> m_machine, mad::core::StateMachine::StateId m_to_state_id) : m_machine(m_machine), m_to_state_id(m_to_state_id){

}
