#ifndef MAD_VISUALEVENT_HPP
#define MAD_VISUALEVENT_HPP

#include <event/Event.hpp>

namespace mad::core {

    struct VisualEvent : Event {
        enum class Type {
            PositionalAppearance,
            Appearance,
            Disappearance
        };

        explicit VisualEvent(Type new_type) : Event(Event::Type::Visual), type(new_type) {
        }

        const Type type;
    };

}

#endif //MAD_VISUALEVENT_HPP
