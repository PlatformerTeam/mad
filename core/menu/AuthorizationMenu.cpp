#include "AuthorizationMenu.hpp"

#include <imgui.h>
#include <spdlog/spdlog.h>


namespace mad::core {

    AuthorizationMenu::AuthorizationMenu(ClientStorageDriver &client_storage_driver) : Menu(Menu::Type::Authorization), m_client_storage_driver(client_storage_driver) { }

    void AuthorizationMenu::render(sf::RenderWindow &window) {
        ImGui::SFML::Update(window, m_delta_clock.restart());
        ImGui::SetNextWindowSize(ImVec2(window.getSize().x, window.getSize().y));
        ImGui::SetNextWindowPos({0, 0});
        switch (m_current_submenu) {
            case SubMenuType::SignInSubMenu: {
                ImGui::Begin("Sign In", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
                char input[255];
                ImGui::InputText(m_hint_phrase.c_str(), input, 255);
                if (ImGui::Button("Enter")) {
                    if (m_client_storage_driver.log_in(input)) {

                    } else {
                        m_hint_phrase = "incorrect login";
                    }
                }
                if (ImGui::Button("Sign Up")) {
                    m_current_submenu = SubMenuType::SignUpSubMenu;
                }
                ImGui::End();
            } break;
            case SubMenuType::SignUpSubMenu: {
                ImGui::Begin("Sign Up", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
                char input[255];
                ImGui::InputText("new login", input, 255);
                if (ImGui::Button("Enter")) {
                    m_client_storage_driver.sign_up(input);
                    m_current_submenu = SubMenuType::SignInSubMenu;
                }
                ImGui::End();
            } break;
        }
        ImGui::SFML::Render(window);
    }


}
