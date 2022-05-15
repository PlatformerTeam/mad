#include "FlyUp.hpp"

mad::core::FlyUp::FlyUp(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity) : Movement(world, entity_id, dir, velocity) {
    Move_animation = ImageStorage::TypeAction::Fly_up;
    Idle_animation = ImageStorage::TypeAction::Fly_up;
}
