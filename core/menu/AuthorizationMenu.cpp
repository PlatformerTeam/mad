#include "AuthorizationMenu.hpp"

#include <event/menu/AuthorizationMenuEvent.hpp>

#include <imgui.h>
#include <spdlog/spdlog.h>


namespace mad::core {

    AuthorizationMenu::AuthorizationMenu(std::shared_ptr<ClientStorageDriver> client_storage_driver) : Menu(Menu::Type::Authorization), m_client_storage_driver(std::move(client_storage_driver)) { }

    bool AuthorizationMenu::render(sf::RenderWindow &window) {
        ImGui::SFML::Update(window, m_delta_clock.restart());
        ImGui::SetNextWindowSize(ImVec2(window.getSize().x, window.getSize().y));
        ImGui::SetNextWindowPos({0, 0});
        switch (m_current_submenu) {
            case SubMenuType::SignInSubMenu: {
                ImGui::Begin("Sign In", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
                ImGui::InputText(m_hint_phrase.c_str(), m_input, 255);
                if (ImGui::Button("Enter")) {
                    if (m_client_storage_driver->log_in(m_input)) {
                        process_menu_event(std::make_shared<AuthorizationMenuEvent>(AuthorizationMenuEvent::Type::Enter));
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
                ImGui::InputText("new login", m_input, 255);
                if (ImGui::Button("Enter")) {
                    m_client_storage_driver->sign_up(m_input);
                    m_current_submenu = SubMenuType::SignInSubMenu;
                }
                ImGui::End();
            } break;
        }
        ImGui::SFML::Render(window);
    }


}
