#ifndef MAD_CORE_WORLD_LOCALWORLD_HPP
#define MAD_CORE_WORLD_LOCALWORLD_HPP

#include <world/World.hpp>
#include <world/entity/EntityStorage.hpp>
#include <event/management/dispatcher/ImmediateDispatcher.hpp>
#include <event/management/dispatcher/DelayedDispatcher.hpp>
#include <box2d/box2d.h>
#include <visual/image/shape/Shape.hpp>
#include <world/entity/ContactListener/ContactListener.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <queue>


namespace mad::core {

    class LocalWorld : public World {
    public:
        explicit LocalWorld(EventDispatcher &event_dispatcher, Vec2d gravitation_scale = {0, 30.0f});

        bool manipulate(const Filter &filter, const Intent &intent) override;

        void produce(EventDispatcher &dispatcher) override;

        Entity & get_entity(Entity::Id id) noexcept override;

        Entity::Id create_viewable_entity(int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<ImageStorage> image_storage) override;

        Entity::Id create_physical_entity(int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<ImageStorage> image_storage,
                                          bool is_fixed = false, bool is_rotated = true) override;

    private:
        std::shared_ptr<std::queue<std::shared_ptr<Event>>> m_step_events_queue;
        std::unique_ptr<DelayedDispatcher> m_event_queue_dispatcher;
        EntityStorage m_storage;
        b2World m_physical_world;
        float dt;
        float render_scale = 3;
        sf::Clock clock;
        float last_time = 0;
        std::shared_ptr<mad::core::MyContactListener> m_contact_listener;
    };

}


#endif //MAD_CORE_WORLD_LOCALWORLD_HPP
