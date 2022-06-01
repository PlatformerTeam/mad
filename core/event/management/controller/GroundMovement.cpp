
#include "GroundMovement.hpp"

mad::core::GroundMovement::GroundMovement(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity) : Movement(world, entity_id, dir, velocity) {
    Move_animation = ImageStorage::TypeAction::Run;
    Idle_animation = ImageStorage::TypeAction::Idle;
}
