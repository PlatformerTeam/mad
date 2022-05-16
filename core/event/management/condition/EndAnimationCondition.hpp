#ifndef MAD_ENDANIMATIONCONDITION_HPP
#define MAD_ENDANIMATIONCONDITION_HPP

#include "Condition.hpp"
#include "visual/image/storage/ImageStorage.hpp"
#include "world/entity/Entity.hpp"
namespace mad::core {
    struct EndAnimationCondition : Condition {
    public:
        explicit EndAnimationCondition(Entity::Id m_entity_id, ImageStorage::TypeAction m_type_action);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        Entity::Id m_entity_id;
        ImageStorage::TypeAction m_type_action;
    };
}// namespace mad::core

#endif//MAD_ENDANIMATIONCONDITION_HPP
