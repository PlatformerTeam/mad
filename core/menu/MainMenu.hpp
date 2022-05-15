#ifndef MAD_MAINMENU_H
#define MAD_MAINMENU_H

#include <menu/Menu.hpp>


namespace mad::core {

    class MainMenu : public Menu {
    public:
        explicit MainMenu();

        bool render(sf::RenderWindow &window) override;
    };

}

#endif //MAD_MAINMENU_H
