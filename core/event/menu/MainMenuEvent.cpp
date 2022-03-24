#include "MainMenuEvent.hpp"

namespace mad::core {

    MainMenuEvent::MainMenuEvent(MainMenuEvent::Kind new_type) : Event(Event::Type::MainMenu), kind(new_type) {}

}
