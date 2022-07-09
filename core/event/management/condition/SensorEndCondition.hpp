#ifndef MAD_SENSORENDCONDITION_HPP
#define MAD_SENSORENDCONDITION_HPP

#include "Condition.hpp"
#include "world/entity/Entity.hpp"
#include <SFML/System/Clock.hpp>
namespace mad::core {
    struct SensorEndCondition : Condition {
    public:
        explicit SensorEndCondition(Entity::Id m_entity_id, float delta_time);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        Entity::Id m_entity_id;
        sf::Clock clock;
        float timerStart;
        float m_dt;
    };
}// namespace mad::core

#endif//MAD_SENSORENDCONDITION_HPP
