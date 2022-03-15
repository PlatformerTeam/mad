#include "VisualEvent.hpp"


namespace mad::core {

    VisualEvent::VisualEvent(VisualEvent::Kind new_kind) : Event(Event::Type::Visual), kind(new_kind) {
    }

}
