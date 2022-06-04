#ifndef MAD_ATTACK_HPP
#define MAD_ATTACK_HPP

#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class Attack : public Movement {
    public:
        Attack(std::shared_ptr<mad::core::LocalWorld> world, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, Entity::Id entity_id, Direction dir, int* attack_stage, float velocity = 0);
        void control() override;
        int *attack_stage;
    private:
        std::shared_ptr<mad::core::LocalWorld> world;
        Entity::Id entity_id;
        PhysicalEntity* m_entity;
        std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher;
    };

}

#endif//MAD_ATTACK_HPP
