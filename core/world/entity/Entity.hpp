#ifndef MAD_CORE_WORLD_ENTITY_ENTITY_HPP
#define MAD_CORE_WORLD_ENTITY_ENTITY_HPP

#include <common/Error.hpp>

#include <cstdint>
#include <unordered_set>


namespace mad::core {
    class World;

    class Intent;

    class EventDispatcher;
}


namespace mad::core {

    class Entity {
    public:
        using Id = std::int32_t;

        const std::unordered_set<std::string> tags;

        explicit Entity(std::unordered_set<std::string> tags);

        virtual void accept(World &world, const Intent &intent, EventDispatcher &dispatcher) = 0;

        [[nodiscard]] Id get_id() const noexcept;

        virtual ~Entity() = default;

    private:
        const Id m_id{};
    };

}


#endif //MAD_CORE_WORLD_ENTITY_ENTITY_HPP
