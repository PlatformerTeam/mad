#ifndef MAD_AUTHORIZATIONMENU_HPP
#define MAD_AUTHORIZATIONMENU_HPP

#include <menu/Menu.hpp>
#include <database/driver/ClientStorageDriver.hpp>

#include <memory>


namespace mad::core {

    class AuthorizationMenu : public Menu {
    public:
        explicit AuthorizationMenu(std::shared_ptr<ClientStorageDriver> client_storage_driver);

        void render(sf::RenderWindow &window) override;

    private:
        enum class SubMenuType {
            SignInSubMenu,
            SignUpSubMenu,
        };

        SubMenuType m_current_submenu = SubMenuType::SignInSubMenu;
        std::shared_ptr<ClientStorageDriver> m_client_storage_driver;
        std::string m_hint_phrase = "login";
        char m_input[255] = "";
    };

}

#endif //MAD_AUTHORIZATIONMENU_HPP
