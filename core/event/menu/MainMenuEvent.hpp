#ifndef MAD_MAINMENUEVENT_HPP
#define MAD_MAINMENUEVENT_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct MainMenuEvent : public Event {
        enum class Kind {
            Quit,
            NewGame,
        };

        explicit MainMenuEvent(Kind new_type);

        const Kind kind;
    };

}

#endif //MAD_MAINMENUEVENT_HPP
