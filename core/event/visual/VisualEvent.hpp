#ifndef MAD_VISUALEVENT_H
#define MAD_VISUALEVENT_H

#include <event/Event.hpp>


namespace mad::core {

    struct VisualEvent : public Event {
        enum class Type {
            PositionalAppearance
        };

        explicit VisualEvent(Type new_type);

        const Type type;
    };

}

#endif //MAD_VISUALEVENT_H
