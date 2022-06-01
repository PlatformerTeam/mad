
#include "SensorEndCondition.hpp"
#include "common/Cast.hpp"
#include "event/physics/SensorCollisionEnd.hpp"
#include <SFML/System/Time.hpp>

mad::core::SensorEndCondition::SensorEndCondition(Entity::Id m_entity_id, float delta_time) : m_entity_id(m_entity_id), m_dt(delta_time){
}
bool mad::core::SensorEndCondition::is_triggered_by(const mad::core::Event &event) {
    if(event.type == Event::Type::SensorCollisionEnd){
        const auto &e = const_cast_to<SensorCollisionEnd>(event);
        if(e.m_id == m_entity_id){
            sf::Time time = clock.getElapsedTime();
            timerStart = time.asSeconds();
        }
    }
    return clock.getElapsedTime().asSeconds() - timerStart < m_dt;

}
std::unordered_set<mad::core::Event::Type> mad::core::SensorEndCondition::triggers() {
    return {mad::core::Event::Type::SensorCollisionEnd, mad::core::Event::Type::WorldUpdate};
}
void mad::core::SensorEndCondition::on_start() {
}
