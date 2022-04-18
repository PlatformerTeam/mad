#ifndef MAD_COLLISION_HPP
#define MAD_COLLISION_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct Collision : public Event {
        explicit Collision(int new_first_object_id, int new_second_object_id);

        const int first_object_id;
        const int second_object_id;
    };

}

#endif//MAD_COLLISION_HPP
