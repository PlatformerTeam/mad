#ifndef MAD_ENEMYATTACKCONDITION_HPP
#define MAD_ENEMYATTACKCONDITION_HPP

#include "Condition.hpp"
#include "world/LocalWorld.hpp"
#include "world/entity/Entity.hpp"
#include <world/entity/PhysicalEntity.hpp>
namespace mad::core {
    struct EnemyAttackCondition : Condition {
    public:
        EnemyAttackCondition(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id hero_id, Entity::Id enemy_id);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        Entity::Id hero_id;
        Entity::Id enemy_id;
        PhysicalEntity* hero_entity;
        PhysicalEntity* enemy_entity;
        std::shared_ptr<mad::core::LocalWorld> world;

    };
}// namespace mad::core


#endif//MAD_ENEMYATTACKCONDITION_HPP
