#include "Mob.hpp"

#include <utility>

mad::core::Mob::Mob(std::unordered_set<std::string> tags, std::int32_t id, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, b2World &physicalWorld, bool is_fixed) : PhysicalEntity(std::move(tags), id, z_ind, initial_position, initial_rotation, std::move(image), physicalWorld, is_fixed) {
}
