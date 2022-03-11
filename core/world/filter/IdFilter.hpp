#ifndef MAD_IDFILTER_HPP
#define MAD_IDFILTER_HPP

#include "Filter.hpp"

namespace mad::core {

    struct IdFilter : Filter {
        explicit IdFilter(Entity::Id filter_id) : Filter(Filter::Type::Id), m_filter_id(filter_id) {
        }

        [[nodiscard]] std::vector<Entity::Id> get_filter_ids() const noexcept {
            return m_filter_id;
        }

    private:
        std::vector<Entity::Id> m_filter_id;

    };

}

#endif //MAD_IDFILTER_HPP
