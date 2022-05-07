#include "AuthorizationMenuEvent.hpp"


namespace mad::core {

    AuthorizationMenuEvent::AuthorizationMenuEvent(AuthorizationMenuEvent::Type new_type) : MenuEvent(MenuEvent::Type::AuthorizationMenu), authorization_menu_type(new_type) { }

}
