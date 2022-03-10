#ifndef MAD_CORE_WORLD_EVENT_EVENT_HPP
#define MAD_CORE_WORLD_EVENT_EVENT_HPP


namespace mad::core {

    struct Event {
        enum class Type {
            Visual,
            Collision,
            Movement,
            Keystroke,
        };

        explicit Event(Type new_type);

        const Type type;
    };

}


#endif //MAD_CORE_WORLD_EVENT_EVENT_HPP
