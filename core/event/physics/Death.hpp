#ifndef MAD_DEATH_HPP
#define MAD_DEATH_HPP

#include "event/Event.hpp"
namespace mad::core {

    struct Death : public Event {
        explicit Death(int entity_id);

        const int entity_id;
    };

}



#endif//MAD_DEATH_HPP
