#include <event/management/EventProducer.hpp>
#include "event/management/dispatcher/EventDispatcher.hpp"
#include <event/Event.hpp>
#include <runner/SequentialRunner.hpp>
#include <common/Error.hpp>

#include <iostream>

namespace dummy {
    using namespace mad::core;

    class Producer : public EventProducer {
    public:
        void produce(EventDispatcher &dispatcher) override {
            dispatcher.dispatch(std::shared_ptr<Event>(
                    new Event{Event::Type::Movement}
            ));
        }
    };

    class Dispatcher : public EventDispatcher {
    public:
        void registry(std::shared_ptr<EventHandler> handler) override {
            NOT_IMPLEMENTED
        }

        void dispatch(std::shared_ptr<Event> event) override {
            NOT_IMPLEMENTED
        }
    };
}

int main(int argc, char *argv[]) {
}
