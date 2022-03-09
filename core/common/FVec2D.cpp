#include "FVec2D.hpp"

namespace mad::core {

    Vec2d::Vec2d(float x, float y) : m_x(x), m_y(y) { }

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