#include "KeyHeld.hpp"

namespace mad::core {

    KeyHeld::KeyHeld(int new_key_id) : Event(Event::Type::KeyHeld), key_id(new_key_id) {}

}
