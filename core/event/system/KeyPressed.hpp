#ifndef MAD_KEYPRESSED_HPP
#define MAD_KEYPRESSED_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct KeyPressed : public Event {
        explicit KeyPressed(int new_key_id);

        const int key_id;
    };

}


#endif //MAD_KEYPRESSED_HPP
