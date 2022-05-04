#include "MainMenu.hpp"

#include <event/menu/MainMenuEvent.hpp>

#include <imgui.h>
#include <spdlog/spdlog.h>


namespace mad::core {

    MainMenu::MainMenu() : Menu(Menu::Type::Main) { }

    void MainMenu::render(sf::RenderWindow &window) {
        ImGui::SFML::Update(window, m_delta_clock.restart());
        ImGui::Begin("Main menu");
        if (ImGui::Button("Start game")) {
            process_menu_event(std::make_shared<MainMenuEvent>(MainMenuEvent::Type::NewGame));
        }
        if (ImGui::Button("Quit")) {
            process_menu_event(std::make_shared<MainMenuEvent>(MainMenuEvent::Type::Quit));
        }
        ImGui::End();
        ImGui::SFML::Render(window);
    }
}
