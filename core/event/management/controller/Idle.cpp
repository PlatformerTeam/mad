#include "Idle.hpp"
mad::core::Idle::Idle(std::shared_ptr<mad::core::LocalWorld> world, mad::core::Entity::Id entity_id) : m_world(world), m_entity_id(entity_id){
    m_entity = cast_to_or_null<PhysicalEntity>(m_world->get_storage().get_entity(m_entity_id));
}

void mad::core::Idle::control() {
    m_entity->set_action(ImageStorage::TypeAction::Idle);
}
