#include "Keystroke.hpp"

namespace mad::core {

    Keystroke::Keystroke(int new_key_id) : Event(Event::Type::Keystroke), key_id(new_key_id) {}

}
