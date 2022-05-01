#ifndef MAD_PAUSEMENU_HPP
#define MAD_PAUSEMENU_HPP

#include <menu/Menu.hpp>


namespace mad::core {

    class PauseMenu : public Menu {
    public:
        explicit PauseMenu();

        void render(sf::RenderWindow &window) override;
    };

}

#endif//MAD_PAUSEMENU_HPP
