#ifndef MAD_SYSTEMLISTENER_H
#define MAD_SYSTEMLISTENER_H

#include <event/management/EventProducer.hpp>
#include <event/management/EventDispatcher.hpp>


namespace mad::core {

    class SystemListener : public EventProducer {
    public:
        void produce(EventDispatcher &dispatcher) override;
    };

}


#endif //MAD_SYSTEMLISTENER_H
