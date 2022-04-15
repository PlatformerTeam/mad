#include "FVec2D.hpp"

namespace mad::core {

    Vec2d::Vec2d(float x, float y) : m_x(x), m_y(y) { }

    float Vec2d::get_x() const noexcept {
        return m_x;
    }

    float Vec2d::get_y() const noexcept {
        return m_y;
    }

    Vec2d &Vec2d::operator+=(const Vec2d &v) {
        m_x += v.m_x;
        m_y += v.m_y;
        return *this;
    }

    Vec2d &Vec2d::operator-=(const Vec2d &v) {
        m_x -= v.m_x;
        m_y -= v.m_y;
        return *this;
    }

    Vec2d &Vec2d::operator*=(float k) {
        m_x *= k;
        m_y *= k;
        return *this;
    }
    Vec2d::operator sf::Vector2<float>() const {
        return {get_x(), get_y()};
    }
    Vec2d::operator b2Vec2() const {
        return {get_x(), get_y()};
    }

    Vec2d operator+(Vec2d v1, const Vec2d &v2) {
        return v1 += v2;
    }

    Vec2d operator-(Vec2d v1, const Vec2d &v2) {
        return v1 -= v2;
    }

    Vec2d operator*(Vec2d v, float k) {
        return v *= k;
    }

    Vec2d operator*(float k, Vec2d v) {
        return v *= k;
    }
}
