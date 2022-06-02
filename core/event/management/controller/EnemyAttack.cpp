#include "EnemyAttack.hpp"
mad::core::EnemyAttack::EnemyAttack(std::shared_ptr<mad::core::LocalWorld> world, mad::core::Entity::Id entity_id, mad::core::Movement::Direction dir, int* attack_stage, float velocity) :  Movement(world, entity_id, dir, velocity), attack_stage(attack_stage){
    Move_animation = ImageStorage::TypeAction::Attack_1_beg;
    Idle_animation = ImageStorage::TypeAction::Attack_1_beg;
}
void mad::core::EnemyAttack::control() {
    Movement::control();
    if((*attack_stage) % 2 == 0){
        if(Move_animation != ImageStorage::TypeAction::Attack_1_beg){
            SPDLOG_DEBUG("changed to Attack_1_beg");
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
