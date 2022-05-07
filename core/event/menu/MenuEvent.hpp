#ifndef MAD_MENUEVENT_HPP
#define MAD_MENUEVENT_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct MenuEvent : Event {
        enum class Type {
            MainMenu,
            PauseMenu,
            AuthorizationMenu,
        };

        explicit MenuEvent(Type new_type);

        const Type type;
    };

}

#endif //MAD_MENUEVENT_HPP
