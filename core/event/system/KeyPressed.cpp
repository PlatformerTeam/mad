#include "KeyPressed.hpp"

namespace mad::core {

    KeyPressed::KeyPressed(int new_key_id) : Event(Event::Type::KeyPressed), key_id(new_key_id) {}

}
