#include "AuthorizationMenu.hpp"

#include <imgui.h>
#include <spdlog/spdlog.h>


namespace mad::core {

    AuthorizationMenu::AuthorizationMenu(ClientStorageDriver &client_storage_driver) : Menu(Menu::Type::Authorization), m_client_storage_driver(client_storage_driver) { }

    void AuthorizationMenu::render(sf::RenderWindow &window) {
        ImGui::SFML::Update(window, m_delta_clock.restart());
        switch (m_current_submenu) {
            case SubMenuType::SignInSubMenu:
                ImGui::Begin("Sign In");

                ImGui::End();
                break;
            case SubMenuType::SignUpSubMenu:
                ImGui::Begin("Sign Up");

                ImGui::End();
                break;
            default:
                ImGui::Begin("Authorization");

                ImGui::End();
                break;
        }
        ImGui::SFML::Render(window);
    }


}
