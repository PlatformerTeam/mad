#ifndef MAD_CORE_WORLD_EVENT_EVENT_HPP
#define MAD_CORE_WORLD_EVENT_EVENT_HPP


namespace mad::core {

    struct Event {
        enum class Type {
            Visual,
            Collision,
            Movement,
            KeyPressed,
            KeyReleased,
            KeyHeld,
            WindowClose,
            Menu,
            LevelPause,
            Runner,
            WorldUpdate,
            EndOfRenderAction,
            SensorCollision,
            SensorCollisionEnd,
        };

        explicit Event(Type new_type);

        const Type type;

        virtual ~Event() = default;
    };

}


#endif //MAD_CORE_WORLD_EVENT_EVENT_HPP
