
#ifndef MAD_RADIUSFILTER_HPP
#define MAD_RADIUSFILTER_HPP

#include "Filter.hpp"
#include "common/FVec2D.hpp"

namespace mad::core {

    struct RadiusFilter : Filter {
        explicit RadiusFilter(Vec2d p, float r) : Filter(Filter::Type::Radius), p(p), r(r) {
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

    private:
        Vec2d p;
        float r;

    };

}


#endif//MAD_RADIUSFILTER_HPP