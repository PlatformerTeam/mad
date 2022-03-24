#include "MenuEvent.hpp"

namespace mad::core {

    MenuEvent::MenuEvent(Type new_type) : Event(Event::Type::Menu), type(new_type) {}

}
