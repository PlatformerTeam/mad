#ifndef MAD_CONTROLLER_HPP
#define MAD_CONTROLLER_HPP

#include "world/entity/EntityStorage.hpp"
#include <event/management/handler/EventHandler.hpp>
namespace mad::core {

    class Controller : public EventHandler {
    public:
        explicit Controller();

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

        virtual void control(EntityStorage &m_storage) = 0;

    private:

    };

}

#endif//MAD_CONTROLLER_HPP
