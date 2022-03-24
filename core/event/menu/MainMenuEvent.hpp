#ifndef MAD_MAINMENUEVENT_HPP
#define MAD_MAINMENUEVENT_HPP

#include <event/menu/MenuEvent.hpp>


namespace mad::core {

    struct MainMenuEvent : public MenuEvent {
        enum class Type {
            Quit,
            NewGame,
        };

        explicit MainMenuEvent(Type new_type);

        const Type type;
    };

}

#endif //MAD_MAINMENUEVENT_HPP
