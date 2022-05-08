#ifndef MAD_CONTROLLER_HPP
#define MAD_CONTROLLER_HPP

 #include <world/entity/EntityStorage.hpp>
 #include <event/management/handler/EventHandler.hpp>
 namespace mad::core {

     class Controller {
     public:
         Controller() = default;

         virtual void control() = 0;

         virtual ~Controller() = default;
     };

 }

#endif//MAD_CONTROLLER_HPP
