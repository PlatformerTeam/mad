#ifndef MAD_TOMAINMENU_H
#define MAD_TOMAINMENU_H

#include <event/menu/PauseMenuEvent.hpp>


namespace mad::core {

    struct ToMainMenu : public PauseMenuEvent {
        explicit ToMainMenu();
    };

}

#endif //MAD_TOMAINMENU_H
