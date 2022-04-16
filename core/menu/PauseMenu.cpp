#include "PauseMenu.hpp"

#include <event/menu/PauseMenuEvent.hpp>

#include <imgui.h>
#include <spdlog/spdlog.h>


namespace mad::core {

    PauseMenu::PauseMenu() : Menu(Menu::Type::Pause) { }

    void PauseMenu::render(sf::RenderWindow &window) {
        ImGui::SFML::Update(window, m_delta_clock.restart());
        if (ImGui::Button("Continue")) {
            process_menu_event(std::make_shared<PauseMenuEvent>(PauseMenuEvent::Type::Continue));
        }
        if (ImGui::Button("Exit to main menu")) {
            process_menu_event(std::make_shared<PauseMenuEvent>(PauseMenuEvent::Type::ToMainMenu));
        }
        ImGui::SFML::Render(window);
    }

}
