#ifndef MAD_CONTINUE_H
#define MAD_CONTINUE_H

#include <event/menu/PauseMenuEvent.hpp>


namespace mad::core {

    struct Continue : public PauseMenuEvent {
        explicit Continue();
    };

}

#endif //MAD_CONTINUE_H
