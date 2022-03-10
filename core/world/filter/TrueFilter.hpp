#ifndef MAD_TRUEFILTER_HPP
#define MAD_TRUEFILTER_HPP

#include "Filter.hpp"

namespace mad::core {

    struct TrueFilter : Filter {

        TrueFilter() : Filter(Filter::Type::True) {
        }

        [[nodiscard]] std::vector<Entity::Id> filter(const EntityStorage &entity_storage) const override {
            std::vector<Entity::Id> entities_ids;
            for (const auto& entity : entity_storage.get_list_entities()) {
                entities_ids.push_back(entity->get_id());
            }
            return entities_ids;
        }

    };

}

#endif //MAD_TRUEFILTER_HPP
