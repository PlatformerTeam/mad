#ifndef MAD_DEALDAMAGE_HPP
#define MAD_DEALDAMAGE_HPP


#include "Controller.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class DealDamage : public Controller {
    public:
        explicit DealDamage(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher);

        void control() override;
    private:
        std::shared_ptr<mad::core::LocalWorld> world;
        Entity::Id entity_id;
        PhysicalEntity* m_entity;
        std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher;
    };

}


#endif//MAD_DEALDAMAGE_HPP
