#include "Run.hpp"
#include "world/intent/LambdaIntent.hpp"
mad::core::Run::Run(std::shared_ptr<mad::core::World> world, Entity::Id entity_id, Direction dir) : m_world(world), m_entity_id(entity_id), dir(dir){
}
void mad::core::Run::control() {

    auto force = [](mad::core::Vec2d dir) {
        return mad::core::LambdaIntent(
                [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                    mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_force_to_center(dir, event_dispatcher);
                });
    };
    //SPDLOG_DEBUG("controller 2");
    if(dir == Direction::Right){
        m_world->manipulate_entity_id(m_entity_id, force(mad::core::Vec2d{100000.0f, 0.0f}));
    }
    else if(dir == Direction::Left){
        m_world->manipulate_entity_id(m_entity_id, force(mad::core::Vec2d{-100000.0f, 0.0f}));
    }

}
