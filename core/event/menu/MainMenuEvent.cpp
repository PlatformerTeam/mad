#include "MainMenuEvent.hpp"

namespace mad::core {

    MainMenuEvent::MainMenuEvent(MainMenuEvent::Type new_type) : MenuEvent(MenuEvent::Type::MainMenu), type(new_type) {}

}
