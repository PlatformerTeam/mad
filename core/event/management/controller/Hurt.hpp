#ifndef MAD_HURT_HPP
#define MAD_HURT_HPP


#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class Hurt : public Movement {
    public:
        Hurt(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity = 0);
    };

}




#endif//MAD_HURT_HPP
