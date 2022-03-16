#include "KeyReleased.hpp"

namespace mad::core {

    KeyReleased::KeyReleased(int new_key_id) : Event(Event::Type::KeyReleased), key_id(new_key_id) {}

}
