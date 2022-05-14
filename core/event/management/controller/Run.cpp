#include "Run.hpp"
#include "world/intent/LambdaIntent.hpp"
#include <world/filter/IdFilter.hpp>
mad::core::Run::Run(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir) : m_world(world), m_entity_id(entity_id), dir(dir){
    m_entity = cast_to_or_null<PhysicalEntity>(m_world->get_storage().get_entity(m_entity_id));
}
void mad::core::Run::control() {

    auto force = [](mad::core::Vec2d dir) {
        return mad::core::LambdaIntent(
                [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                    mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_force_to_center(dir, event_dispatcher);
                });
    };
    //SPDLOG_DEBUG("controller 2");
    m_entity->set_action(ImageStorage::TypeAction::Run);
    if(dir == Direction::Right){
        m_world->manipulate_entity_id(m_entity_id, force(mad::core::Vec2d{100000.0f, 0.0f}));
    }
    else if(dir == Direction::Left){
        m_world->manipulate_entity_id(m_entity_id, force(mad::core::Vec2d{-100000.0f, 0.0f}));
    }


}
