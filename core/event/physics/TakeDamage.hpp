#ifndef MAD_TAKEDAMAGE_HPP
#define MAD_TAKEDAMAGE_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct TakeDamage : public Event {
        explicit TakeDamage(int entity_id);

        const int entity_id;
    };

}



#endif//MAD_TAKEDAMAGE_HPP
