#include "PauseMenu.hpp"

#include <spdlog/spdlog.h>


namespace mad::core {

    PauseMenu::PauseMenu() : Menu(Menu::Type::Pause) { }

    void PauseMenu::render(sf::RenderWindow &window) {
        SPDLOG_INFO("OVERRIDE!");
    }

}
