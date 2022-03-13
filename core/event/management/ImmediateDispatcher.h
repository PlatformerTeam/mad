#ifndef MAD_IMMEDIATEDISPATCHER_H
#define MAD_IMMEDIATEDISPATCHER_H
#include "EventDispatcher.hpp"
namespace mad::core {

    class ImmediateDispatcher : public EventDispatcher{
    public:
        virtual void registry(std::shared_ptr<EventHandler> handler);
        virtual void dispatch(std::shared_ptr<Event> event);

        virtual ~ImmediateDispatcher() = default;
    };

}
#endif//MAD_IMMEDIATEDISPATCHER_H
