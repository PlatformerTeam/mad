#ifndef MAD_CORE_EVENT_MANAGEMENT_EVENTHANDLER_HPP
#define MAD_CORE_EVENT_MANAGEMENT_EVENTHANDLER_HPP

#include <event/Event.hpp>

#include <unordered_set>


namespace mad::core {

    class EventHandler {
    public:
        virtual void handle(const Event &event) = 0;
        virtual std::unordered_set<Event::Type> handled_types() = 0;

        virtual ~EventHandler() = default;
    };

}// namespace mad::core


#endif//MAD_CORE_EVENT_MANAGEMENT_EVENTHANDLER_HPP
