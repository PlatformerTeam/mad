#ifndef MAD_CORE_EVENT_MANAGEMENT_EVENTPRODUCER_HPP
#define MAD_CORE_EVENT_MANAGEMENT_EVENTPRODUCER_HPP

#include <chrono>


namespace mad::core {
    class EventDispatcher;
}

namespace mad::core {

    class EventProducer {
    public:
        virtual void produce(EventDispatcher &) = 0;

        virtual ~EventProducer() = default;

    protected:
        virtual void produce_impl(EventDispatcher &) = 0;
    };

}


#endif //MAD_CORE_EVENT_MANAGEMENT_EVENTPRODUCER_HPP
