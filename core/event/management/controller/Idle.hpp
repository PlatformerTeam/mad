#ifndef MAD_IDLE_HPP
#define MAD_IDLE_HPP
#include "Controller.hpp"
#include "world/LocalWorld.hpp"

namespace mad::core {

    class Idle : public Controller {
    public:
        explicit Idle(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id);

        void control() override;

    private:
        std::shared_ptr<mad::core::LocalWorld> m_world;
        Entity::Id m_entity_id;
        PhysicalEntity* m_entity;
    };

}


#endif//MAD_IDLE_HPP
