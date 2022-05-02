#ifndef MAD_LEVELPAUSE_HPP
#define MAD_LEVELPAUSE_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct LevelPause : public Event {
        explicit LevelPause();
    };

}

#endif//MAD_LEVELPAUSE_HPP
