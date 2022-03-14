#ifndef MAD_CORE_WORLD_LOCALWORLD_HPP
#define MAD_CORE_WORLD_LOCALWORLD_HPP

#include <world/World.hpp>
#include <world/entity/EntityStorage.hpp>
#include <event/management/dispatcher/ImmediateDispatcher.hpp>

#include <queue>


namespace mad::core {
    class DelayedDispatcher;
}

namespace mad::core {

    class LocalWorld : public World {
    public:
        LocalWorld();

        bool manipulate(const Filter &filter, const Intent &intent) override;

        void produce(EventDispatcher &dispatcher) override;

    private:
        std::shared_ptr<std::queue<std::shared_ptr<Event>>> m_step_events_queue;
        std::unique_ptr<DelayedDispatcher> m_event_queue_dispatcher;
        EntityStorage m_storage;
    };

}


#endif //MAD_CORE_WORLD_LOCALWORLD_HPP
