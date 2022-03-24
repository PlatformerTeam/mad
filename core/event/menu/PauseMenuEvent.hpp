#ifndef MAD_PAUSEMENUEVENT_HPP
#define MAD_PAUSEMENUEVENT_HPP

#include <event/menu/MenuEvent.hpp>


namespace mad::core {

    struct PauseMenuEvent : public MenuEvent {
        enum class Type {
            Continue,
            ToMainMenu,
        };

        explicit PauseMenuEvent(Type new_type);

        const Type type;
    };

}

#endif //MAD_PAUSEMENUEVENT_HPP
