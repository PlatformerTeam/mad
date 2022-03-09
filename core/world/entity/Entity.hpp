#ifndef MAD_CORE_WORLD_ENTITY_ENTITY_HPP
#define MAD_CORE_WORLD_ENTITY_ENTITY_HPP

#include <cstdint>


namespace mad::core {
    class World;

    class Intent;

    class EventDispatcher;
}


namespace mad::core {

    class Entity {
    public:
        using Id = std::int32_t;

    public:
        virtual void accept(World &world, Intent &intent, EventDispatcher &) = 0;

        [[nodiscard]] Id get_id() const noexcept;

        virtual ~Entity() = 0;

    private:
        const Id m_id;
    };

}


#endif //MAD_CORE_WORLD_ENTITY_ENTITY_HPP