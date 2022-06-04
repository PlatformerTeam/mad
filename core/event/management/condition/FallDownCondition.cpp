#include "FallDownCondition.hpp"
mad::core::FallDownCondition::FallDownCondition(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id m_entity_id) : m_entity_id(m_entity_id){
    enemy_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(m_entity_id));
}
std::unordered_set<mad::core::Event::Type> mad::core::FallDownCondition::triggers() {
    return {Event::Type::WorldUpdate};
}
bool mad::core::FallDownCondition::is_triggered_by(const mad::core::Event &event) {
    if(enemy_entity->get_position().get_y() > 250) return true;
    return false;
}
void mad::core::FallDownCondition::on_start() {
}
