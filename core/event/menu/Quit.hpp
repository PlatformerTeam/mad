#ifndef MAD_QUIT_HPP
#define MAD_QUIT_HPP

#include <event/menu/MainMenuEvent.hpp>


namespace mad::core {

    struct Quit : public MainMenuEvent {
        explicit Quit();
    };

}

#endif //MAD_QUIT_HPP
