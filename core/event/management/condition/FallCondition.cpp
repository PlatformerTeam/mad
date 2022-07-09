#include "FallCondition.hpp"



bool mad::core::FallCondition::is_triggered_by(const mad::core::Event &event) {
    return m_entity->get_linear_velocity().get_y() >= vel;
}
std::unordered_set<mad::core::Event::Type> mad::core::FallCondition::triggers() {
    return {mad::core::Event::Type::WorldUpdate};
}
void mad::core::FallCondition::on_start() {
}
mad::core::FallCondition::FallCondition(std::shared_ptr<mad::core::LocalWorld> world, mad::core::Entity::Id entity_id, float vel) : m_world(world), m_entity_id(entity_id), vel(vel) {
    m_entity = cast_to_or_null<PhysicalEntity>(m_world->get_storage().get_entity(m_entity_id));
}
