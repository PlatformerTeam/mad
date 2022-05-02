#ifndef MAD_TAGFILTER_HPP
#define MAD_TAGFILTER_HPP

#include "Filter.hpp"

#include <utility>

namespace mad::core {

    struct TagFilter : Filter {
        explicit TagFilter(std::string filter_tag) : Filter(Filter::Type::EntityTag), m_filter_tag(std::move(filter_tag)) {
        }

        [[nodiscard]] std::string get_filter_tag() const noexcept {
            return m_filter_tag;
        }

    private:
        std::string m_filter_tag;

    };

}// namespace mad::core

#endif//MAD_TAGFILTER_HPP
