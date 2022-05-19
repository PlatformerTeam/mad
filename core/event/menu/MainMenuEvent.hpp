#ifndef MAD_MAINMENUEVENT_HPP
#define MAD_MAINMENUEVENT_HPP

#include <event/menu/MenuEvent.hpp>


namespace mad::core {

    struct MainMenuEvent : MenuEvent {
        enum class Type {
            Quit,
            NewGame,
        };

        explicit MainMenuEvent(Type new_type);

        const Type main_menu_event_type;
    };

}

#endif //MAD_MAINMENUEVENT_HPP
