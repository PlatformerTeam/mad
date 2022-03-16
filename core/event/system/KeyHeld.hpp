#ifndef MAD_KEYHELD_H
#define MAD_KEYHELD_H

#include <event/Event.hpp>


namespace mad::core {

    struct KeyHeld : public Event {
        explicit KeyHeld(int new_key_id);

        const int key_id;
    };

}


#endif //MAD_KEYHELD_H
