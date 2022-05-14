#include "KeyPressedCondition.hpp"
#include <common/Cast.hpp>
#include <event/system/KeyPressed.hpp>
std::unordered_set<mad::core::Event::Type> mad::core::KeyPressedCondition::triggers() {
    return {mad::core::Event::Type::KeyPressed};
}
bool mad::core::KeyPressedCondition::is_triggered_by(const mad::core::Event &event) {
    const auto &keystroke = const_cast_to<KeyPressed>(event);
    return keystroke.key_id == m_key_id;
}

mad::core::KeyPressedCondition::KeyPressedCondition(const int m_key_id) : m_key_id(m_key_id){
}
void mad::core::KeyPressedCondition::on_start() {
}
