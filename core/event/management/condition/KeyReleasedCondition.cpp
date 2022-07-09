#include "KeyReleasedCondition.hpp"
#include <common/Cast.hpp>
#include <event/system/KeyReleased.hpp>
std::unordered_set<mad::core::Event::Type> mad::core::KeyReleasedCondition::triggers() {
    return {mad::core::Event::Type::KeyReleased};
}
bool mad::core::KeyReleasedCondition::is_triggered_by(const mad::core::Event &event) {
    const auto &keystroke = const_cast_to<KeyReleased>(event);
    return keystroke.key_id == m_key_id;
}

mad::core::KeyReleasedCondition::KeyReleasedCondition(const int m_key_id) : m_key_id(m_key_id){
}
void mad::core::KeyReleasedCondition::on_start() {
}
