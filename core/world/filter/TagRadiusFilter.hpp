#ifndef MAD_TAGRADIUSFILTER_HPP
#define MAD_TAGRADIUSFILTER_HPP

#include "Filter.hpp"
#include <common/FVec2D.hpp>
#include <utility>
namespace mad::core {

    struct TagRadiusFilter : Filter {
        explicit TagRadiusFilter(Vec2d m_point, float m_radius, std::string type) : Filter(Filter::Type::TagRadius), m_point(m_point), m_radius(m_radius), m_tag(std::move(type)) {
        }

        [[nodiscard]] float get_filter_radius() const noexcept {
            return m_radius;
        }

        [[nodiscard]] float get_filter_radius_sq() const noexcept {
            return m_radius * m_radius;
        }

        [[nodiscard]] Vec2d get_filter_point() const noexcept {
            return m_point;
        }

        [[nodiscard]] std::string get_filter_tag() const noexcept {
            return m_tag;
        }

    private:
        Vec2d m_point;
        float m_radius;
        std::string m_tag;

    };

}


#endif//MAD_TAGRADIUSFILTER_HPP
