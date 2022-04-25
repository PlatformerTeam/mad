#ifndef MAD_TAGRADIUSFILTER_HPP
#define MAD_TAGRADIUSFILTER_HPP

#include "Filter.hpp"
#include <common/FVec2D.hpp>
namespace mad::core {

    struct TagRadiusFilter : Filter {
        explicit TagRadiusFilter(Vec2d p, float r, Entity::Type type) : Filter(Filter::Type::TagRadius), p(p), r(r), m_filter_tag(type) {
        }

        [[nodiscard]] float get_filter_radius() const noexcept {
            return r;
        }

        [[nodiscard]] float get_filter_radius_sq() const noexcept {
            return r * r;
        }

        [[nodiscard]] Vec2d get_filter_point() const noexcept {
            return p;
        }

        [[nodiscard]] Entity::Type get_filter_tag() const noexcept {
            return m_filter_tag;
        }

    private:
        Vec2d p;
        float r;
        Entity::Type m_filter_tag;

    };

}


#endif//MAD_TAGRADIUSFILTER_HPP
