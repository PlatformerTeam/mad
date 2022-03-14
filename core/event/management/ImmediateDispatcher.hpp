#ifndef MAD_IMMEDIATEDISPATCHER_HPP
#define MAD_IMMEDIATEDISPATCHER_HPP
#include "event/management/EventDispatcher.hpp"
#include "memory"
namespace mad::core {

    class ImmediateDispatcher : public EventDispatcher{
    public:
        virtual void registry(std::shared_ptr<EventHandler> handler);
        virtual void dispatch(std::shared_ptr<Event> event);
    };

}
#endif//MAD_IMMEDIATEDISPATCHER_HPP
