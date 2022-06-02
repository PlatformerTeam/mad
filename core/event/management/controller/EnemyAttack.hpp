#ifndef MAD_ENEMYATTACK_HPP
#define MAD_ENEMYATTACK_HPP


#include "Movement.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class EnemyAttack : public Movement {
    public:
        EnemyAttack(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, int* attack_stage, float velocity = 0);
        void control() override;
        int *attack_stage;
    };

}


#endif//MAD_ENEMYATTACK_HPP
