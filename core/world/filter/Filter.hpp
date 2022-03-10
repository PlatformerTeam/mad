#ifndef MAD_CORE_WORLD_FILTER_FILTER_HPP
#define MAD_CORE_WORLD_FILTER_FILTER_HPP

#include <world/entity/Entity.hpp>
#include <world/entity/EntityStorage.hpp>
#include <memory>

namespace mad::core {

    struct Filter {
        enum class Type {
            Lambda,
            Id,
            Tag,
            True
        };

        explicit Filter(Type new_type) : type(new_type) {
        }

        virtual std::vector<Entity::Id> filter(const EntityStorage &entity_storage) = 0;

        const Type type;
    };

}


#endif //MAD_CORE_WORLD_FILTER_FILTER_HPP
