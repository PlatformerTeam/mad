#include "GameRunnerEvent.hpp"


namespace mad::core {

    GameRunnerEvent::GameRunnerEvent(Type new_type) : RunnerEvent(RunnerEvent::Type::GameRunner), game_runner_event_type(new_type) { }

}
