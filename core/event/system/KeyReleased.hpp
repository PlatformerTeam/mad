#ifndef MAD_KEYRELEASED_HPP
#define MAD_KEYRELEASED_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct KeyReleased : public Event {
        explicit KeyReleased(int new_key_id);

        const int key_id;
    };

}


#endif //MAD_KEYRELEASED_HPP
