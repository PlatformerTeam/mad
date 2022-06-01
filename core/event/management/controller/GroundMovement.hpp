#ifndef MAD_GROUNDMOVEMENT_HPP
#define MAD_GROUNDMOVEMENT_HPP

#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class GroundMovement : public Movement {
    public:
        GroundMovement(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity = 0);
    };

}

#endif//MAD_GROUNDMOVEMENT_HPP
