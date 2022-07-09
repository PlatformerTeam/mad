#include "LocalWorld.hpp"
#include "event/WorldUpdate.hpp"

#include <common/Error.hpp>
#include <event/management/dispatcher/DelayedDispatcher.hpp>
#include <spdlog/spdlog.h>
#include <world/entity/ContactListener/ContactListener.hpp>
#include <world/entity/Entity.hpp>
#include <world/filter/TrueFilter.hpp>
#include <world/intent/LambdaIntent.hpp>

#include <vector>


mad::core::LocalWorld::LocalWorld(EventDispatcher &event_dispatcher, Vec2d gravitation_scale)
    : m_step_events_queue(std::make_shared<std::queue<std::shared_ptr<Event>>>()),
      m_event_queue_dispatcher(std::make_unique<DelayedDispatcher>(m_step_events_queue)),
      m_physical_world(b2World(b2Vec2(gravitation_scale.get_x(), gravitation_scale.get_y()))) {

    m_contact_listener = std::make_shared<mad::core::MyContactListener>(event_dispatcher);
    m_physical_world.SetContactListener(&*m_contact_listener);
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
    //Update event
    dispatcher.dispatch(std::make_shared<WorldUpdate>());


    // calculating fps + dt
    sf::Time time = clock.getElapsedTime();
    dt = time.asSeconds() - last_time;
    sf::sleep(sf::seconds((1.0f/120) - dt));
    last_time = time.asSeconds();
    float fact_dt = (1.0f/120);

    //double fps = 1 / (time.asSeconds() - l_old);
    //SPDLOG_INFO("FPS {}", fps);

    // simulating physics
    m_physical_world.Step(fact_dt * render_scale, 3, 10);
    for (Entity::Id entity_id : m_storage.extract(TrueFilter())) {
        if (auto physical_entity = cast_to_or_null<PhysicalEntity>(m_storage.get_entity(entity_id)); physical_entity != nullptr) {
            physical_entity->synchronize_position_with_viewable();
            if(abs(physical_entity->get_linear_velocity().get_y()) > 0.01){
                //SPDLOG_DEBUG("vel {}", physical_entity->get_linear_velocity().get_y());
            }
        }
    }

    // collision

    /*for (b2Contact *contact = m_physical_world.GetContactList(); contact; contact = contact->GetNext()) {
        contact->IsTouching()
    }
    for (Entity::Id entity_id : m_storage.extract(TrueFilter())) {
        if (cast_to_or_null<PhysicalEntity>(m_storage.get_entity(entity_id)) != nullptr) {
            auto physical_entity = cast_to_or_null<PhysicalEntity>(m_storage.get_entity(entity_id));
            for (b2ContactEdge *edge = physical_entity->body->GetContactList(); edge; edge = edge->next) {
                if (edge.)
            }
            physical_entity->synchronize_position_with_viewable();
        }
    }*/


    // dispatching events
    while (!m_step_events_queue->empty()) {
        dispatcher.dispatch(m_step_events_queue->front());
        m_step_events_queue->pop();
    }
}

mad::core::Entity::Id mad::core::LocalWorld::create_viewable_entity(int z_ind, mad::core::Vec2d initial_position, float initial_rotation,
                                                                    std::shared_ptr<ImageStorage> image_storage) {
    return m_storage.create_viewable_entity(z_ind, initial_position, initial_rotation, image_storage);
}
mad::core::Entity::Id mad::core::LocalWorld::create_physical_entity(int z_ind, mad::core::Vec2d initial_position, float initial_rotation,
                                                                    std::shared_ptr<ImageStorage> image_storage, bool is_fixed, bool is_rotated, uint16 categoryBits, uint16 maskBits) {
    return m_storage.create_physical_entity(z_ind, initial_position, initial_rotation, image_storage,
                                            m_physical_world, is_fixed, is_rotated, categoryBits, maskBits);
}

mad::core::Entity &mad::core::LocalWorld::get_entity(mad::core::Entity::Id id) noexcept {
    return m_storage.get_entity(id);
}
mad::core::EntityStorage &mad::core::LocalWorld::get_storage() {
    return m_storage;
}
