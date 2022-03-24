#include "PauseMenuEvent.hpp"

namespace mad::core {

    PauseMenuEvent::PauseMenuEvent(PauseMenuEvent::Kind new_type) : Event(Event::Type::PauseMenu), kind(new_type) {}

}
