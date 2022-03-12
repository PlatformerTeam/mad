#ifndef MAD_IMMEDIATEDISPATCHER_HPP
#define MAD_IMMEDIATEDISPATCHER_HPP

#include "EventDispatcher.hpp"

#include <common/Error.hpp>

#include <unordered_map>
#include <vector>

namespace mad::core {

    class ImmediateDispatcher : public EventDispatcher {
    public:
        void registry(std::shared_ptr<EventHandler> handler) override;

        void dispatch(std::shared_ptr<Event> event) override;

    private:
        std::unordered_map<Event::Type, std::vector<EventHandler>> m_
    };

}

#endif //MAD_IMMEDIATEDISPATCHER_HPP
