#ifndef MAD_FALLCONDITION_HPP
#define MAD_FALLCONDITION_HPP

#include "Condition.hpp"
#include "visual/image/storage/ImageStorage.hpp"
#include "world/LocalWorld.hpp"
#include "world/entity/Entity.hpp"
#include "world/entity/PhysicalEntity.hpp"
namespace mad::core {
    struct FallCondition : Condition {
    public:
        explicit FallCondition(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, float vel);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        std::shared_ptr<mad::core::LocalWorld> m_world;
        Entity::Id m_entity_id;
        PhysicalEntity *m_entity;
        float vel;
    };
}// namespace mad::core

#endif//MAD_FALLCONDITION_HPP
