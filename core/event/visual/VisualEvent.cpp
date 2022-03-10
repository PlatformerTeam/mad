#include "VisualEvent.hpp"


namespace mad::core {

    VisualEvent::VisualEvent(VisualEvent::Type new_type) : Event(Event::Type::Visual), type(new_type) {
    }

}
