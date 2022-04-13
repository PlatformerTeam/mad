
#include "CollisionHandler.hpp"
#include <spdlog/spdlog.h>
#include <event/physics/Collision.hpp>
#include <common/Cast.hpp>
#include <world/entity/Entity.hpp>
#include <world/entity/PhysicalEntity.hpp>
#include <world/intent/LambdaIntent.hpp>
#include <event/Event.hpp>
mad::core::CollisionHandler::CollisionHandler()= default;

/*auto color = [](mad::core::Vec2d dir) {
    return mad::core::LambdaIntent(
            [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                mad::core::cast_to<mad::core::ViewableEntity>(entity).m_image;
            });
};*/

void mad::core::CollisionHandler::handle(const mad::core::Event &event) {
    const auto &collision = const_cast_to<Collision>(event);
    Entity::Id id_A = collision.first_object_id;
    Entity::Id id_B = collision.second_object_id;
    SPDLOG_INFO("handle collision {0} {1}", id_A, id_B);
    /*m_world->manipulate_entity_id(m_entity_id, impulse(mad::core::Vec2d{0.0f, -200000.0f}));
    auto physical_entity_A = cast_to_or_null<PhysicalEntity>(m_storage.get_entity(entity_id));
    physical_entity->synchronize_position_with_viewable();*/
}
std::unordered_set<mad::core::Event::Type> mad::core::CollisionHandler::handled_types() {
    return {Event::Type::Collision};
}
