#ifndef MAD_CORE_EVENT_MANAGEMENT_EVENTPRODUCER_HPP
#define MAD_CORE_EVENT_MANAGEMENT_EVENTPRODUCER_HPP


namespace mad::core {
    class EventDispatcher;
}

namespace mad::core {

    class EventProducer {
    public:
        virtual void produce(EventDispatcher &) = 0;

        virtual ~EventProducer() = default;
    };

}


#endif //MAD_CORE_EVENT_MANAGEMENT_EVENTPRODUCER_HPP
