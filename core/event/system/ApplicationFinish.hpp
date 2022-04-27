#ifndef MAD_APPLICATIONFINISH_HPP
#define MAD_APPLICATIONFINISH_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct ApplicationFinish : Event {
        explicit ApplicationFinish();
    };

}

#endif //MAD_APPLICATIONFINISH_HPP
