#include "ImmediateDispatcher.hpp"

namespace mad::core {

    void ImmediateDispatcher::registry(std::shared_ptr<EventHandler> handler) {
        for (const auto &types : handler->handled_types()) {
            m_handlers_for_types[types].push_back(handler);
        }
    }

    void ImmediateDispatcher::dispatch(std::shared_ptr<Event> event) {
        for (auto &handler : m_handlers_for_types[event->type]) {
            handler->handle(*event);
        }
    }

}

