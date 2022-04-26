#include "PauseMenuEvent.hpp"

namespace mad::core {

    PauseMenuEvent::PauseMenuEvent(PauseMenuEvent::Type new_type) : MenuEvent(MenuEvent::Type::PauseMenu), pause_menu_event_type(new_type) {}

}
