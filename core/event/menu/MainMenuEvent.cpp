#include "MainMenuEvent.hpp"

namespace mad::core {

    MainMenuEvent::MainMenuEvent(MainMenuEvent::Type new_type) : MenuEvent(MenuEvent::Type::MainMenu), main_menu_event_type(new_type) {}

}
