#include "TakeDamageCondition.hpp"
#include "common/Cast.hpp"
#include "event/physics/TakeDamage.hpp"
mad::core::TakeDamageCondition::TakeDamageCondition(Entity::Id m_entity_id) : m_entity_id(m_entity_id) {
}
bool mad::core::TakeDamageCondition::is_triggered_by(const mad::core::Event &event) {
    if(event.type == Event::Type::TakeDamage){
        const auto &e = const_cast_to<TakeDamage>(event);
        if(e.entity_id == m_entity_id){
            return true;
        }
    }
    return false;
}
std::unordered_set<mad::core::Event::Type> mad::core::TakeDamageCondition::triggers() {
    return {mad::core::Event::Type::TakeDamage};
}
void mad::core::TakeDamageCondition::on_start() {
}
