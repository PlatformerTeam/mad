#ifndef MAD_VISUALEVENT_H
#define MAD_VISUALEVENT_H

#include <event/Event.hpp>


namespace mad::core {

    struct VisualEvent : public Event {
        enum class Kind {
            PositionalAppearance
        };

        explicit VisualEvent(Kind new_type);

        const Kind kind;
    };

}

#endif //MAD_VISUALEVENT_H