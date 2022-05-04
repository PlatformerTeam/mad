#include "Square.hpp"

namespace mad::core {

    Square::Square(float side, Color color = {255,255,255}) : Shape(Shape::Geometry::Square, color), m_side(side) {
    }

    float Square::get_side_length() const noexcept {
        return m_side;
    }

    b2PolygonShape Square::as_fixture() {
        b2PolygonShape fixture;
        fixture.SetAsBox(m_side / 2, m_side / 2);
        return fixture;
    }

} // mad::core::Square
