#include "Die.hpp"
mad::core::Die::Die(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity) : Movement(world, entity_id, dir, velocity) {
    Move_animation = ImageStorage::TypeAction::Die;
    Idle_animation = ImageStorage::TypeAction::Die;
}