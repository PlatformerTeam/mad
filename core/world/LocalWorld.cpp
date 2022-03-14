#include "LocalWorld.hpp"

#include <world/entity/Entity.hpp>
#include <common/Error.hpp>
#include <event/management/dispatcher/DelayedDispatcher.hpp>

#include <vector>


mad::core::LocalWorld::LocalWorld()
        : m_step_events_queue(std::make_shared<std::queue<std::shared_ptr<Event>>>()),
          m_event_queue_dispatcher(std::make_unique<DelayedDispatcher>(m_step_events_queue)) {}


bool mad::core::LocalWorld::manipulate(const mad::core::Filter &filter, const mad::core::Intent &intent) {
    //CHECK_THROW(is_legal(validate_filter(f), IllegalManipulation, "Illegal filter");
    //CHECK_THROW(is_legal(validate_intent(i), IllegalManipulation, "Illegal intent");

    for (Entity::Id entity_id: m_storage.extract(filter)) {
        m_storage.get_entity(entity_id).accept(*this, intent, *m_event_queue_dispatcher);
    }

    return true;
}


void mad::core::LocalWorld::produce(mad::core::EventDispatcher &dispatcher) {
    while (!m_step_events_queue->empty()) {
        dispatcher.dispatch(m_step_events_queue->front());
        m_step_events_queue->pop();
    }
}

mad::core::Entity::Id mad::core::LocalWorld::create_viewable_entity(int z_ind, mad::core::Vec2d initial_position,
                                                                    std::shared_ptr<Image> image) {
    return m_storage.create_viewable_entity(z_ind, initial_position, image);
}
