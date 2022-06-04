#ifndef MAD_DIE_HPP
#define MAD_DIE_HPP

#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class Die : public Movement {
    public:
        Die(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity = 0);
    };

}

#endif//MAD_DIE_HPP
