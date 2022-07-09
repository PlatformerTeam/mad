#ifndef MAD_FLYUP_HPP
#define MAD_FLYUP_HPP


#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class FlyUp : public Movement {
    public:
        FlyUp(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity = 0);
    };

}

#endif//MAD_FLYUP_HPP
