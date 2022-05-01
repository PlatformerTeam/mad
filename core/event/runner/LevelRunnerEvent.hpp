#ifndef MAD_LEVELRUNNEREVENT_HPP
#define MAD_LEVELRUNNEREVENT_HPP

#include <event/runner/RunnerEvent.hpp>


namespace mad::core {

    struct LevelRunnerEvent : RunnerEvent {
        enum class Type {
            ApplicationFinish,
            LevelStop,
        };

        explicit LevelRunnerEvent(Type new_type);

        const Type level_runner_event_type;
    };

}


#endif//MAD_LEVELRUNNEREVENT_HPP
