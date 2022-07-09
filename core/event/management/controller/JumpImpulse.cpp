#include "JumpImpulse.hpp"
#include "world/intent/LambdaIntent.hpp"
mad::core::JumpImpulse::JumpImpulse(std::shared_ptr<mad::core::World> world, Entity::Id entity_id, float m_impulse) : m_world(world), m_entity_id(entity_id), m_impulse(m_impulse) {
}
void mad::core::JumpImpulse::control() {

    auto impulse = [](mad::core::Vec2d dir) {
        return mad::core::LambdaIntent(
                [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                    mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_linear_impulse_to_center(dir, event_dispatcher);
                });
    };

    m_world->manipulate_entity_id(m_entity_id, impulse(mad::core::Vec2d{0.0f, -m_impulse}));
}
