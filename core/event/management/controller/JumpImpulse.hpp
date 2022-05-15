#ifndef MAD_JUMPIMPULSE_HPP
#define MAD_JUMPIMPULSE_HPP

#include "Controller.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"
namespace mad::core {

    class JumpImpulse : public Controller {
    public:

        explicit JumpImpulse(std::shared_ptr<mad::core::World> world, Entity::Id entity_id);

        void control() override;

    private:
        std::shared_ptr<mad::core::World> m_world;
        Entity::Id m_entity_id;
        std::shared_ptr<int> key;

    };

}

#endif//MAD_JUMPIMPULSE_HPP
