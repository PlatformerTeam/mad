#ifndef MAD_KEYSTROKE_H
#define MAD_KEYSTROKE_H

#include <event/Event.hpp>


namespace mad::core {

    struct Keystroke : Event {
        explicit Keystroke(int new_key_id);

        const int key_id;
    };

}


#endif //MAD_KEYSTROKE_H
