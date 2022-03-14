#ifndef MAD_CORE_EVENT_MANAGEMENT_DISPATCHER_DELAYEDDISPATCHER_HPP
#define MAD_CORE_EVENT_MANAGEMENT_DISPATCHER_DELAYEDDISPATCHER_HPP

#include <event/management/dispatcher/EventDispatcher.hpp>

#include <queue>


namespace mad::core {
    class Event;
}

namespace mad::core {

    class DelayedDispatcher : public EventDispatcher {
    public:
        explicit DelayedDispatcher(std::shared_ptr<std::queue<std::shared_ptr<Event>>> delayed_events)
                : m_delayed_events(std::move(delayed_events)) {}

        void registry(std::shared_ptr<EventHandler> handler) override;

        void dispatch(std::shared_ptr<Event> event) override;

    private:
        std::shared_ptr<std::queue<std::shared_ptr<Event>>> m_delayed_events;
    };
}


#endif //MAD_CORE_EVENT_MANAGEMENT_DISPATCHER_DELAYEDDISPATCHER_HPP
