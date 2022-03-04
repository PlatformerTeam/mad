#include "EventProducer.hpp"

#include <common/Error.hpp>


void mad::core::EventProducer::produce(mad::core::EventDispatcher &dispatcher) {
    NOT_IMPLEMENTED
    produce_impl(dispatcher);
}

std::chrono::milliseconds mad::core::EventProducer::step_duration() {
    NOT_IMPLEMENTED
}
