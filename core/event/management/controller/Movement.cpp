#include "Movement.hpp"
#include "world/intent/LambdaIntent.hpp"
mad::core::Movement::Movement(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, mad::core::Movement::Direction dir, float velocity) : m_world(world), m_entity_id(entity_id), dir(dir), velocity(velocity){
    m_entity = cast_to_or_null<PhysicalEntity>(m_world->get_storage().get_entity(m_entity_id));
}
void mad::core::Movement::control() {
    auto set_horizontal_velocity = [](float vel) {
        return mad::core::LambdaIntent(
                [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                    mad::core::cast_to<mad::core::PhysicalEntity>(entity).set_linear_horizontal_velocity(vel, event_dispatcher);
                });
    };
    if(dir == Direction::Right || dir == Direction::Left){
        m_entity->set_action(Move_animation);
        if(dir == Direction::Right){
            m_entity->flip_over(Image::Orientation::Right);
            m_world->manipulate_entity_id(m_entity_id, set_horizontal_velocity(velocity));
        }
        else if(dir == Direction::Left){
            m_entity->flip_over(Image::Orientation::Left);
            m_world->manipulate_entity_id(m_entity_id, set_horizontal_velocity(-velocity));
        }
    }
    else if(dir == Direction::Idle){
        m_entity->set_action(Idle_animation);
    }
    float k = 0.8;
    m_world->manipulate_entity_id(m_entity_id, set_horizontal_velocity(m_entity->get_linear_velocity().get_x() * k));
}
