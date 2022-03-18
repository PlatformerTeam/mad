#ifndef MAD_CORE_WORLD_LOCALWORLD_HPP
#define MAD_CORE_WORLD_LOCALWORLD_HPP

#include <world/World.hpp>
#include <world/entity/EntityStorage.hpp>
#include <event/management/dispatcher/ImmediateDispatcher.hpp>
#include <event/management/dispatcher/DelayedDispatcher.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <queue>
#include "box2d/box2d.h"
#include "visual/image/shape/Shape.hpp"


namespace mad::core {

    class LocalWorld : public World {
    public:
        LocalWorld();

        bool manipulate(const Filter &filter, const Intent &intent) override;

        void produce(EventDispatcher &dispatcher) override;

        Entity::Id create_viewable_entity(int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image) override;

        Entity::Id create_physical_entity(int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, bool is_Fixed = false) override;

    private:
        std::shared_ptr<std::queue<std::shared_ptr<Event>>> m_step_events_queue;
        std::unique_ptr<DelayedDispatcher> m_event_queue_dispatcher;
        EntityStorage m_storage;
        b2World physicalWorld;
        float dt;
        float render_scale = 5;
        sf::Clock clock;
        float lastTime = 0;
    };

}


#endif //MAD_CORE_WORLD_LOCALWORLD_HPP
