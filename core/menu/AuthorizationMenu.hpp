#ifndef MAD_AUTHORIZATIONMENU_HPP
#define MAD_AUTHORIZATIONMENU_HPP

#include <menu/Menu.hpp>
#include <database/driver/ClientStorageDriver.hpp>


namespace mad::core {

    class AuthorizationMenu : public Menu {
    public:
        explicit AuthorizationMenu(ClientStorageDriver &client_storage_driver);

        void render(sf::RenderWindow &window) override;

    private:
        enum class SubMenuType {
            SignInSubMenu,
            SignUpSubMenu,
            MainSubMenu,
        };

        SubMenuType m_current_submenu = SubMenuType::MainSubMenu;
        ClientStorageDriver &m_client_storage_driver;
    };

}

#endif //MAD_AUTHORIZATIONMENU_HPP
