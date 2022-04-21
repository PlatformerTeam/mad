#include "Mob.hpp"

mad::core::Mob::Mob(Entity::Type e_type, std::int32_t id, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, b2World &physicalWorld, bool is_fixed) : PhysicalEntity(e_type, id, z_ind, initial_position, initial_rotation, image, physicalWorld, is_fixed) {
}
