#include "EntityStorage.hpp"

#include <common/Error.hpp>


namespace mad::core {

    std::vector<Entity::Id> EntityStorage::extract(const Filter &filter) const {
        switch (filter.type) {
            case Filter::Type::Id: {
                IdFilter id_filter = const_cast_to<IdFilter>(filter);
                return id_filter.get_filter_ids();
            }

            case Filter::Type::True: {
                return m_list_ids;
            }
            case Filter::Type::Lambda:
                break;
            case Filter::Type::Tag:
                break;
        }
    }

    Entity &EntityStorage::get_entity(Entity::Id id) {
        auto entity_it = m_map_entities.find(id);
        CHECK_THROW(entity_it != m_map_entities.end(), InvalidArgument, "Entity with given id does not exist");
        return *entity_it->second;
    }
}
