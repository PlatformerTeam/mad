#include "AuthorizationMenuEvent.hpp"


namespace mad::core {

    AuthorizationMenuEvent::AuthorizationMenuEvent(AuthorizationMenuEvent::Type new_type) : MenuEvent(MenuEvent::Type::AuthorizationMenu), auth_menu_type(new_type) { }

}
