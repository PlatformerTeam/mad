#include "MainMenu.hpp"

#include <spdlog/spdlog.h>


namespace mad::core {

    MainMenu::MainMenu() : Menu(Menu::Type::Main) { }

    void MainMenu::render(sf::RenderWindow &window) {
        SPDLOG_INFO("OVERRIDE!");
    }
}
