#ifndef MAD_CORE_WORLD_ENTITY_ENTITY_HPP
#define MAD_CORE_WORLD_ENTITY_ENTITY_HPP

#include <common/Error.hpp>

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

        enum class Type {
            Enemy,
            SimpleObject,
            Hero,
        };

        const Type type;

        explicit Entity(Type new_type);
        virtual void accept(World &world, const Intent &intent, EventDispatcher &dispatcher) = 0;

        [[nodiscard]] Id get_id() const noexcept;

        virtual ~Entity() = default;

    private:
        const Id m_id{};
    };

}


#endif //MAD_CORE_WORLD_ENTITY_ENTITY_HPP
