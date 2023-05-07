#include "Destroy.hpp"
#include "event/physics/Death.hpp"
#include "world/intent/LambdaIntent.hpp"
mad::core::Destroy::Destroy(std::shared_ptr<mad::core::LocalWorld> world, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, mad::core::Entity::Id entity_id) : world(world), level_dispatcher(level_dispatcher), entity_id(entity_id) {
    m_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(entity_id));
}
void mad::core::Destroy::control() {
    auto set_position = []() {
        return mad::core::LambdaIntent(
                [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                    mad::core::cast_to<mad::core::PhysicalEntity>(entity).set_image_position({-10000, -10000});
                });
    };
    level_dispatcher->dispatch(std::make_shared<Death>(entity_id));
    world->manipulate_entity_id(entity_id, set_position());
}
