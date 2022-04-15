#ifndef MAD_PAUSEMENU_HPP
#define MAD_PAUSEMENU_HPP

#include <menu/Menu.hpp>


namespace mad::core {

    class PauseMenu : public Menu {
    public:
        explicit PauseMenu();

        virtual void exit_to_main_menu() = 0;

        virtual void close_and_continue() = 0;
    };

}

#endif//MAD_PAUSEMENU_HPP
