#ifndef MAD_TAKEDAMAGECONDITION_HPP
#define MAD_TAKEDAMAGECONDITION_HPP

#include "Condition.hpp"
#include "world/entity/Entity.hpp"
#include <SFML/System/Clock.hpp>
namespace mad::core {
    struct TakeDamageCondition : Condition {
    public:
        explicit TakeDamageCondition(Entity::Id m_entity_id);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        Entity::Id m_entity_id;

    };
}// namespace mad::core


#endif//MAD_TAKEDAMAGECONDITION_HPP
