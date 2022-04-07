#ifndef MAD_WINDOWCLOSE_HPP
#define MAD_WINDOWCLOSE_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct WindowClose : public Event {
        explicit WindowClose();
    };

}

#endif //MAD_WINDOWCLOSE_HPP
