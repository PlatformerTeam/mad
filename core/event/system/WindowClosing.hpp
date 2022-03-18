#ifndef MAD_WINDOWCLOSING_HPP
#define MAD_WINDOWCLOSING_HPP

#include <event/Event.hpp>


namespace mad::core {

    struct WindowClosing : public Event {
        explicit WindowClosing();
    };

}

#endif //MAD_WINDOWCLOSING_HPP
