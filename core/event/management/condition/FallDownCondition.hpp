#ifndef MAD_FALLDOWNCONDITION_HPP
#define MAD_FALLDOWNCONDITION_HPP
#include "Condition.hpp"
#include "world/LocalWorld.hpp"
#include "world/entity/Entity.hpp"
#include "world/entity/PhysicalEntity.hpp"
#include <SFML/System/Clock.hpp>
namespace mad::core {
    struct FallDownCondition : Condition {
    public:
        explicit FallDownCondition(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id m_entity_id);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        Entity::Id m_entity_id;
        PhysicalEntity* enemy_entity;

    };
}// namespace mad::core
#endif//MAD_FALLDOWNCONDITION_HPP
