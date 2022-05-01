#include "LevelRunnerEvent.hpp"

namespace mad::core {

    LevelRunnerEvent::LevelRunnerEvent(Type new_type) : RunnerEvent(RunnerEvent::Type::LevelRunner), level_runner_event_type(new_type) { }

}
