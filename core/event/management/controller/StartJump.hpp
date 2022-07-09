#ifndef MAD_STARTJUMP_HPP
#define MAD_STARTJUMP_HPP

#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class StartJump : public Movement {
    public:
        StartJump(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity = 0);
    };

}

#endif//MAD_STARTJUMP_HPP
