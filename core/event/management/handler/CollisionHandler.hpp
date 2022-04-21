#ifndef MAD_COLLISIONHANDLER_HPP
#define MAD_COLLISIONHANDLER_HPP

#include "EventHandler.hpp"
#include <event/Event.hpp>
namespace mad::core {

    class CollisionHandler : public EventHandler {
    public:
        explicit CollisionHandler();

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:

    };

}

#endif//MAD_COLLISIONHANDLER_HPP
