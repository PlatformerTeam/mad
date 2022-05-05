#ifndef MAD_CONTROLLER_HPP
#define MAD_CONTROLLER_HPP

#include <event/management/handler/EventHandler.hpp>
#include <world/entity/EntityStorage.hpp>
namespace mad::core {

    class Controller {
    public:
        Controller() = default;

        virtual void control() = 0;
    };

}// namespace mad::core
#endif//MAD_CONTROLLER_HPP
