#ifndef MAD_CORE_EVENT_MANAGEMENT_DISPATCHER_HPP
#define MAD_CORE_EVENT_MANAGEMENT_DISPATCHER_HPP

#include <memory>


namespace mad::core {
    class EventHandler;
    struct Event;
}

namespace mad::core {

    class EventDispatcher {
    public:
        virtual void registry(std::shared_ptr<EventHandler> handler) = 0;
        virtual void dispatch(std::shared_ptr<Event> event) = 0;

        virtual ~EventDispatcher() = default;
    };

}


#endif //MAD_CORE_EVENT_MANAGEMENT_DISPATCHER_HPP
