#ifndef MAD_GAMERUNNEREVENT_HPP
#define MAD_GAMERUNNEREVENT_HPP

#include <event/runner/RunnerEvent.hpp>


namespace mad::core {

    struct GameRunnerEvent : RunnerEvent {
        enum class Type {
            ApplicationFinish,
            GameStop,
        };

        explicit GameRunnerEvent(Type new_type);

        const Type game_runner_event_type;
    };

}

#endif//MAD_GAMERUNNEREVENT_HPP
