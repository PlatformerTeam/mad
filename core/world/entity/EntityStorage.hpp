#ifndef MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP
#define MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP

#include <vector>

#include <world/entity/Entity.hpp>
#include <world/filter/Filter.hpp>

namespace mad::core {
    struct Filter;

    class EntityStorage {
    public:
        std::vector<Entity::Id> extract(const Filter &filter) const;

        [[nodiscard]] std::vector<std::shared_ptr<Entity>> get_list_entities() const noexcept;

    private:
        std::vector<std::shared_ptr<Entity>> m_list_entities;
    };

}


#endif //MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP
