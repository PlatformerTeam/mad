#ifndef MAD_CORE_WORLD_FILTER_FILTER_HPP
#define MAD_CORE_WORLD_FILTER_FILTER_HPP

#include <world/entity/Entity.hpp>

#include <memory>
#include <vector>


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

        const Type type;
    };

}


#endif //MAD_CORE_WORLD_FILTER_FILTER_HPP
