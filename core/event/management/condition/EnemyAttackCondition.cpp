#include "EnemyAttackCondition.hpp"
#include "world/filter/RadiusFilter.hpp"
mad::core::EnemyAttackCondition::EnemyAttackCondition(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id hero_id, Entity::Id enemy_id) : world(world), hero_id(hero_id), enemy_id(enemy_id) {
    hero_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(hero_id));
    enemy_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(enemy_id));

}
std::unordered_set<mad::core::Event::Type> mad::core::EnemyAttackCondition::triggers() {
    return {Event::Type::WorldUpdate};
}
bool mad::core::EnemyAttackCondition::is_triggered_by(const mad::core::Event &event) {
    for(auto id : world->get_storage().extract(RadiusFilter(hero_entity->get_position(), 6.0f))){
        if(id == enemy_id){
            return true;
        }
    }
    return false;
}
void mad::core::EnemyAttackCondition::on_start() {
}
