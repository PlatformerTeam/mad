#ifndef MAD_CORE_COMMON_FVEC2D_HPP
#define MAD_CORE_COMMON_FVEC2D_HPP

#include <box2d/box2d.h>
#include <SFML/System/Vector2.hpp>

namespace mad::core {


    class Vec2d {
    public:
        Vec2d(float x, float y);
        operator b2Vec2() const;

        operator sf::Vector2<float>() const;

        [[nodiscard]] float get_x() const noexcept;

        [[nodiscard]] float get_y() const noexcept;

        Vec2d &operator+=(const Vec2d &v);

        Vec2d &operator-=(const Vec2d &v);

        Vec2d &operator*=(float k);

    private:
        float m_x, m_y;
    };

    Vec2d operator+(Vec2d v1, const Vec2d &v2);

    Vec2d operator-(Vec2d v1, const Vec2d &v2);

    Vec2d operator*(Vec2d v, float k);

    Vec2d operator*(float k, Vec2d v);
}

#endif //MAD_CORE_COMMON_FVEC2D_HPP
