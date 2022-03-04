#ifndef MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP
#define MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP

#include <vector>

#include <world/entity/Entity.hpp>


namespace mad::core {
    class Filter;
}


namespace mad::core {

    class EntityStorage {
    public:
        std::vector<Entity::Id> extract(const Filter&);
    };

}


#endif //MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP
