#ifndef MAD_DESTROY_HPP
#define MAD_DESTROY_HPP


#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class Destroy : public Controller {
    public:
        Destroy(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id);
        void control() override;
    };

}



#endif//MAD_DESTROY_HPP
