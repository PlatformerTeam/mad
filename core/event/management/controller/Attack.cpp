#include "Attack.hpp"
#include "event/physics/TakeDamage.hpp"
#include "world/filter/RadiusFilter.hpp"
mad::core::Attack::Attack(std::shared_ptr<mad::core::LocalWorld> world, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, mad::core::Entity::Id entity_id, mad::core::Movement::Direction dir, int* attack_stage, float velocity) :  Movement(world, entity_id, dir, velocity), world(world), level_dispatcher(level_dispatcher), entity_id(entity_id), attack_stage(attack_stage){
    Move_animation = ImageStorage::TypeAction::Attack_1_beg;
    Idle_animation = ImageStorage::TypeAction::Attack_1_beg;
    m_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(entity_id));
}
void mad::core::Attack::control() {
    if((*attack_stage) % 6 == 0){
        if(Move_animation != ImageStorage::TypeAction::Attack_1_beg){
            SPDLOG_DEBUG("changed to Attack_1_beg");
        }
        Move_animation = ImageStorage::TypeAction::Attack_1_beg;
        Idle_animation = ImageStorage::TypeAction::Attack_1_beg;
    }
    if((*attack_stage) % 6 == 1){
        if(Move_animation != ImageStorage::TypeAction::Attack_1_end){
            SPDLOG_DEBUG("changed to Attack_1_end");
        }
        for (auto id : world->get_storage().extract(RadiusFilter(m_entity->get_position(), 10.0f))) {
            level_dispatcher->dispatch(std::make_shared<TakeDamage>(id));
        }
        Move_animation = ImageStorage::TypeAction::Attack_1_end;
        Idle_animation = ImageStorage::TypeAction::Attack_1_end;
    }
    if((*attack_stage) % 6 == 2){
        if(Move_animation != ImageStorage::TypeAction::Attack_2_beg){
            SPDLOG_DEBUG("changed to Attack_2_beg");
        }
        Move_animation = ImageStorage::TypeAction::Attack_2_beg;
        Idle_animation = ImageStorage::TypeAction::Attack_2_beg;
    }
    if((*attack_stage) % 6 == 3){
        if(Move_animation != ImageStorage::TypeAction::Attack_2_end){
            SPDLOG_DEBUG("changed to Attack_2_end");
        }
        for (auto id : world->get_storage().extract(RadiusFilter(m_entity->get_position(), 10.0f))) {
            level_dispatcher->dispatch(std::make_shared<TakeDamage>(id));
        }
        Move_animation = ImageStorage::TypeAction::Attack_2_end;
        Idle_animation = ImageStorage::TypeAction::Attack_2_end;
    }
    if((*attack_stage) % 6 == 4){
        if(Move_animation != ImageStorage::TypeAction::Attack_3_beg){
            SPDLOG_DEBUG("changed to Attack_3_beg");
        }
        for (auto id : world->get_storage().extract(RadiusFilter(m_entity->get_position(), 10.0f))) {
            level_dispatcher->dispatch(std::make_shared<TakeDamage>(id));
        }
        Move_animation = ImageStorage::TypeAction::Attack_3_beg;
        Idle_animation = ImageStorage::TypeAction::Attack_3_beg;
    }
    if((*attack_stage) % 6 == 5){
        if(Move_animation != ImageStorage::TypeAction::Attack_3_end){
            SPDLOG_DEBUG("changed to Attack_3_end");
        }
        for (auto id : world->get_storage().extract(RadiusFilter(m_entity->get_position(), 10.0f))) {
            level_dispatcher->dispatch(std::make_shared<TakeDamage>(id));
        }
        Move_animation = ImageStorage::TypeAction::Attack_3_end;
        Idle_animation = ImageStorage::TypeAction::Attack_3_end;
    }
    Movement::control();
}
