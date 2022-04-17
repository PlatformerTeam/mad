#include "ImmediateDispatcher.hpp"

#include <spdlog/spdlog.h>


namespace mad::core {

    void ImmediateDispatcher::registry(std::shared_ptr<EventHandler> handler) {
        for (const auto &types : handler->handled_types()) {
            m_handlers_for_types[types].push_back(handler);
        }
    }

    void ImmediateDispatcher::dispatch(std::shared_ptr<Event> event) {
//        SPDLOG_INFO("dispatching event {}", event->type);
        for (auto &handler : m_handlers_for_types[event->type]) {
//            SPDLOG_INFO("pass event to handler");
            handler->handle(*event);
        }
    }

}

