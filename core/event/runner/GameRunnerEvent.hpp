#ifndef MAD_GAMERUNNEREVENT_HPP
#define MAD_GAMERUNNEREVENT_HPP

#include <event/runner/RunnerEvent.hpp>


namespace mad::core {

    struct GameRunnerEvent : RunnerEvent {
        explicit GameRunnerEvent();
    };

}

#endif//MAD_GAMERUNNEREVENT_HPP
