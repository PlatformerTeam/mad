#ifndef MAD_SENSORCONDITION_HPP
#define MAD_SENSORCONDITION_HPP
#include "Condition.hpp"
#include "world/entity/Entity.hpp"
namespace mad::core {
    struct SensorCondition : Condition {
    public:
        explicit SensorCondition(Entity::Id m_entity_id);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        Entity::Id m_entity_id;
    };
}// namespace mad::core


#endif//MAD_SENSORCONDITION_HPP
