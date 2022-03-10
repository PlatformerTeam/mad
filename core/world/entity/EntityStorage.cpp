#include "EntityStorage.hpp"

#include <common/Error.hpp>

namespace mad::core {

    std::vector<Entity::Id> EntityStorage::extract(const Filter &filter) {
        filter.filter(this);
    }

    std::vector<std::shared_ptr<Entity>> EntityStorage::get_list_entities() const noexcept {
        return m_list_entities;
    }

}