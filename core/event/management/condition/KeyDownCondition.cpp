#include "KeyDownCondition.hpp"
#include <event/system/KeyHeld.hpp>

#include <common/Cast.hpp>
std::unordered_set<mad::core::Event::Type> mad::core::KeyDownCondition::triggers() {
    return {mad::core::Event::Type::KeyHeld};
}
bool mad::core::KeyDownCondition::is_triggered_by(const mad::core::Event &event) {
    const auto &keystroke = const_cast_to<KeyHeld>(event);
    return keystroke.key_id == m_key_id;
}

mad::core::KeyDownCondition::KeyDownCondition(const int m_key_id) : m_key_id(m_key_id){
}
void mad::core::KeyDownCondition::on_start() {
}
