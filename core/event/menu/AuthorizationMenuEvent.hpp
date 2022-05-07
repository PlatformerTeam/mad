#ifndef MAD_AUTHORIZATIONMENUEVENT_HPP
#define MAD_AUTHORIZATIONMENUEVENT_HPP

#include <event/menu/MenuEvent.hpp>


namespace mad::core {

    struct AuthorizationMenuEvent : MenuEvent {
        enum class Type {
            Enter,
        };

        explicit AuthorizationMenuEvent(Type new_type);

        const Type auth_menu_type;
    };

}


#endif //MAD_AUTHORIZATIONMENUEVENT_HPP
