#ifndef MAD_PAUSEMENUEVENT_HPP
#define MAD_PAUSEMENUEVENT_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct PauseMenuEvent : public Event {
        enum class Kind {
            Continue,
            ToMainMenu,
        };

        explicit PauseMenuEvent(Kind new_type);

        const Kind kind;
    };

}

#endif //MAD_PAUSEMENUEVENT_HPP
