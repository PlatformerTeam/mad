#include "World.hpp"

#include <world/filter/IdFilter.hpp>


namespace mad::core {

    bool World::manipulate_entity_id(Entity::Id entity_id, const Intent &intent) {
        return manipulate(IdFilter(entity_id), intent);
    }

}
