#ifndef MAD_LEVELRUNNEREVENT_HPP
#define MAD_LEVELRUNNEREVENT_HPP

#include <event/runner/RunnerEvent.hpp>


namespace mad::core {

    struct LevelRunnerEvent : RunnerEvent {
        explicit LevelRunnerEvent();
    };

}


#endif//MAD_LEVELRUNNEREVENT_HPP
