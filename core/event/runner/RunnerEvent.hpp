#ifndef MAD_RUNNEREVENT_HPP
#define MAD_RUNNEREVENT_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct RunnerEvent : Event {
        enum class Type {
            GameRunner,
            LevelRunner,
        };

        explicit RunnerEvent(Type new_type);

        const Type type;
    };

}

#endif//MAD_RUNNEREVENT_HPP
