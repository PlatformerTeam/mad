#ifndef MAD_NEWGAME_HPP
#define MAD_NEWGAME_HPP

#include <event/menu/MainMenuEvent.hpp>


namespace mad::core {

    struct NewGame : public MainMenuEvent {
        explicit NewGame();
    };

}

#endif //MAD_NEWGAME_HPP
