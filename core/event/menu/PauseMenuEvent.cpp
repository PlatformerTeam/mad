#include "PauseMenuEvent.hpp"

namespace mad::core {

    PauseMenuEvent::PauseMenuEvent(PauseMenuEvent::Type new_type) : MenuEvent(MenuEvent::Type::PauseMenu), type(new_type) {}

}
