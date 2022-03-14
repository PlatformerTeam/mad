#include "DelayedDispatcher.hpp"

#include <common/Error.hpp>


void mad::core::DelayedDispatcher::registry(std::shared_ptr<EventHandler> handler) {
    FAIL("DelayedDispatcher does not support registry")
}

void mad::core::DelayedDispatcher::dispatch(std::shared_ptr<Event> event) {
    m_delayed_events->push(std::move(event));
}
