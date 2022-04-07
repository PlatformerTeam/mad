#include "LocalWorld.hpp"

#include <world/intent/LambdaIntent.hpp>
#include <world/filter/TrueFilter.hpp>
#include <common/Error.hpp>
#include <event/management/dispatcher/DelayedDispatcher.hpp>
#include <world/entity/Entity.hpp>

#include <vector>


mad::core::LocalWorld::LocalWorld(Vec2d gravitation_scale)
    : m_step_events_queue(std::make_shared<std::queue<std::shared_ptr<Event>>>()),
      m_event_queue_dispatcher(std::make_unique<DelayedDispatcher>(m_step_events_queue)),
      physicalWorld(b2World(b2Vec2(gravitation_scale.get_x(), gravitation_scale.get_y()))) {
}


bool mad::core::LocalWorld::manipulate(const mad::core::Filter &filter, const mad::core::Intent &intent) {
    //CHECK_THROW(is_legal(validate_filter(f), IllegalManipulation, "Illegal filter");
    //CHECK_THROW(is_legal(validate_intent(i), IllegalManipulation, "Illegal intent");

    for (Entity::Id entity_id : m_storage.extract(filter)) {
        m_storage.get_entity(entity_id).accept(*this, intent, *m_event_queue_dispatcher);
    }

    return true;
}


void mad::core::LocalWorld::produce(mad::core::EventDispatcher &dispatcher) {
    sf::Time time = clock.getElapsedTime();
    dt = time.asSeconds() - last_time;
    double fps = 1 / (time.asSeconds() - last_time);
    last_time = time.asSeconds();
    physicalWorld.Step(dt * render_scale, 3, 10);
    for (Entity::Id entity_id : m_storage.extract(TrueFilter())) {

        if (cast_to_or_null<PhysicalEntity>(m_storage.get_entity(entity_id)) != nullptr) {
            auto physical_entity = cast_to_or_null<PhysicalEntity>(m_storage.get_entity(entity_id));
            physical_entity->synchronize_position_with_viewable();
        }
    }
    while (!m_step_events_queue->empty()) {
        dispatcher.dispatch(m_step_events_queue->front());
        m_step_events_queue->pop();
    }
}

mad::core::Entity::Id mad::core::LocalWorld::create_viewable_entity(int z_ind, mad::core::Vec2d initial_position, float initial_rotation,
                                                                    std::shared_ptr<Image> image) {
    return m_storage.create_viewable_entity(z_ind, initial_position, initial_rotation, image);
}
mad::core::Entity::Id mad::core::LocalWorld::create_physical_entity(int z_ind, mad::core::Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, bool is_Fixed) {
    return m_storage.create_physical_entity(z_ind, initial_position, initial_rotation, image, physicalWorld, is_Fixed);
}
