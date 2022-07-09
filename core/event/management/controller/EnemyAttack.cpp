#include "EnemyAttack.hpp"
#include "event/physics/TakeDamage.hpp"
#include "world/filter/RadiusFilter.hpp"
mad::core::EnemyAttack::EnemyAttack(std::shared_ptr<mad::core::LocalWorld> world, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, mad::core::Entity::Id entity_id, mad::core::Movement::Direction dir, int* attack_stage, float velocity) :  Movement(world, entity_id, dir, velocity), world(world), level_dispatcher(level_dispatcher), entity_id(entity_id), attack_stage(attack_stage){
    Move_animation = ImageStorage::TypeAction::Attack_1_beg;
    Idle_animation = ImageStorage::TypeAction::Attack_1_beg;
    m_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(entity_id));
}
void mad::core::EnemyAttack::control() {
    Movement::control();
    if((*attack_stage) % 2 == 0){
        if(Move_animation != ImageStorage::TypeAction::Attack_1_beg){
            SPDLOG_DEBUG("changed to Attack_1_beg");
        }
        for (auto id : world->get_storage().extract(RadiusFilter(m_entity->get_position(), 6.0f))) {
            if(id != entity_id){
                level_dispatcher->dispatch(std::make_shared<TakeDamage>(id));

            }
        }
        Move_animation = ImageStorage::TypeAction::Attack_1_beg;
        Idle_animation = ImageStorage::TypeAction::Attack_1_beg;
    }
    if((*attack_stage) % 2 == 1){
        if(Move_animation != ImageStorage::TypeAction::Attack_1_end){
            SPDLOG_DEBUG("changed to Attack_1_end");
        }
        Move_animation = ImageStorage::TypeAction::Attack_1_end;
        Idle_animation = ImageStorage::TypeAction::Attack_1_end;
    }
}
