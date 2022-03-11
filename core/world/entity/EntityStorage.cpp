#include "EntityStorage.hpp"

namespace mad::core {

    std::vector<Entity::Id> EntityStorage::extract(const Filter &filter) const {
        switch (filter.type) {
            case Filter::Type::Id: {
                IdFilter id_filter = cast_to<IdFilter>(filter);
                return id_filter.get_filter_ids();
            }

            case Filter::Type::True: {
                return m_list_ids;
            }
        }
    }
}