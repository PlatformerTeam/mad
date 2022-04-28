#include "RunnerEvent.hpp"

namespace mad::core {

    RunnerEvent::RunnerEvent(Type new_type) : Event(Event::Type::Runner), type(new_type) { }

}
