#ifndef MAD_IDFILTER_HPP
#define MAD_IDFILTER_HPP

#include "Filter.hpp"

namespace mad::core {

    struct IdFilter : Filter {
        explicit IdFilter(Entity::Id filter_id) : Filter(Filter::Type::Id), m_filter_id(filter_id) {
        }

        [[nodiscard]] std::vector<Entity::Id> filter(const EntityStorage &entity_storage) const override {
            std::vector<Entity::Id> entities_ids;
            for (const auto& entity : entity_storage.get_list_entities()) {
                if (entity->get_id() == m_filter_id) {
                    entities_ids.push_back(entity->get_id());
                }
            }
            return entities_ids;
        }

        [[nodiscard]] Entity::Id get_filter_id() const noexcept {
            return m_filter_id;
        }

    private:
        Entity::Id m_filter_id;

    };

}

#endif //MAD_IDFILTER_HPP
