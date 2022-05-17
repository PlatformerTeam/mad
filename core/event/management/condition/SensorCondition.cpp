#include "SensorCondition.hpp"
#include "common/Cast.hpp"
#include "event/physics/SensorCollision.hpp"
mad::core::SensorCondition::SensorCondition(Entity::Id m_entity_id) : m_entity_id(m_entity_id){
}
bool mad::core::SensorCondition::is_triggered_by(const mad::core::Event &event) {
    const auto &e = const_cast_to<SensorCollision>(event);
    return e.m_id == m_entity_id;
}
std::unordered_set<mad::core::Event::Type> mad::core::SensorCondition::triggers() {
    return {mad::core::Event::Type::SensorCollision};
}
void mad::core::SensorCondition::on_start() {
}
