#ifndef MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP
#define MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP

#include "Entity.hpp"

#include <common/Error.hpp>
#include <common/Cast.hpp>
#include <world/filter/Filter.hpp>
#include <world/filter/IdFilter.hpp>

#include <vector>
#include <unordered_map>

namespace mad::core {

    class EntityStorage {
    public:
        [[nodiscard]] std::vector<Entity::Id> extract(const Filter &filter) const;

    private:
        std::unordered_map<Entity::Id, std::unique_ptr<Entity>> m_map_entities;

        std::vector<Entity::Id> m_list_ids;
    };

}


#endif //MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP
