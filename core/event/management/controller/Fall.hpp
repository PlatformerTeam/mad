#ifndef MAD_FALL_HPP
#define MAD_FALL_HPP

#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class Fall : public Movement {
    public:
        Fall(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity = 0);
    };

}

#endif//MAD_FALL_HPP
