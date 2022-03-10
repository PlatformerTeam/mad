#ifndef MAD_TRUEFILTER_HPP
#define MAD_TRUEFILTER_HPP

#include "Filter.hpp"

namespace mad::core {

    struct TrueFilter : Filter {

        TrueFilter() : Filter(Filter::Type::True) {
        }

        std::vector<Entity::Id> filter(std::shared_ptr<EntityStorage> entity_storage) override {
            std::vector<Entity::Id> entities_ids;
            for (const Entity &entity : EntityStorage.get_list_enteties()) {
                entities_ids.push_back(entity.get_id());
            }
            return entities_ids;
        }

    };

}

#endif //MAD_TRUEFILTER_HPP
