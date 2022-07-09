
#include "DealDamage.hpp"
#include "event/physics/TakeDamage.hpp"
#include "world/filter/RadiusFilter.hpp"

mad::core::DealDamage::DealDamage(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher) : world(world), entity_id(entity_id), level_dispatcher(level_dispatcher) {
    m_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(entity_id));
}
void mad::core::DealDamage::control() {
    for (auto id : world->get_storage().extract(RadiusFilter(m_entity->get_position(), 10.0f))) {
        level_dispatcher->dispatch(std::make_shared<TakeDamage>(id));
    }

}
