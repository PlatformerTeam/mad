#ifndef MAD_PAUSEMENUEVENT_HPP
#define MAD_PAUSEMENUEVENT_HPP

#include <event/menu/MenuEvent.hpp>


namespace mad::core {

    struct PauseMenuEvent : MenuEvent {
        enum class Type {
            Continue,
            ToMainMenu,
        };

        explicit PauseMenuEvent(Type new_type);

        const Type pause_menu_event_type;
    };

}

#endif //MAD_PAUSEMENUEVENT_HPP
