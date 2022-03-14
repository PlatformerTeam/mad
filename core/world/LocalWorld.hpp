#ifndef MAD_CORE_WORLD_LOCALWORLD_HPP
#define MAD_CORE_WORLD_LOCALWORLD_HPP

#include <world/World.hpp>
#include <world/entity/EntityStorage.hpp>
#include <event/management/dispatcher/ImmediateDispatcher.hpp>
#include <event/management/dispatcher/DelayedDispatcher.hpp>

#include <queue>


namespace mad::core {

    class LocalWorld : public World {
    public:
        LocalWorld();

        bool manipulate(const Filter &filter, const Intent &intent) override;

        void produce(EventDispatcher &dispatcher) override;

        Entity::Id create_viewable_entity(int z_ind, Vec2d initial_position, std::shared_ptr<Image> image) override;

    private:
        std::shared_ptr<std::queue<std::shared_ptr<Event>>> m_step_events_queue;
        std::unique_ptr<DelayedDispatcher> m_event_queue_dispatcher;
        EntityStorage m_storage;
    };

}


#endif //MAD_CORE_WORLD_LOCALWORLD_HPP
