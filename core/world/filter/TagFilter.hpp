#ifndef MAD_TAGFILTER_HPP
#define MAD_TAGFILTER_HPP

#include "Filter.hpp"

namespace mad::core {

    struct TagFilter : Filter {
        explicit TagFilter(Entity::Type filter_tag) : Filter(Filter::Type::EntityTag), m_filter_tag(filter_tag) {
        }

        [[nodiscard]] Entity::Type get_filter_tag() const noexcept {
            return m_filter_tag;
        }

    private:
        Entity::Type m_filter_tag;

    };

}

#endif //MAD_TAGFILTER_HPP
