#include "PauseMenu.hpp"

#include <event/menu/PauseMenuEvent.hpp>

#include <imgui.h>
#include <spdlog/spdlog.h>


namespace mad::core {

    PauseMenu::PauseMenu() : Menu(Menu::Type::Pause) { }

    bool PauseMenu::render(sf::RenderWindow &window) {
        ImGui::SFML::Update(window, m_delta_clock.restart());
        ImGui::SetNextWindowSize(ImVec2(window.getSize().x, window.getSize().y));
        ImGui::SetNextWindowPos({0, 0});
        ImGui::Begin("Pause menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        if (ImGui::Button("Continue")) {
            process_menu_event(std::make_shared<PauseMenuEvent>(PauseMenuEvent::Type::Continue));
        }
        if (ImGui::Button("Exit to main menu")) {
            process_menu_event(std::make_shared<PauseMenuEvent>(PauseMenuEvent::Type::ToMainMenu));
        }
        ImGui::End();
        ImGui::SFML::Render(window);
        return true;
    }

}
