#include "Square.hpp"

namespace mad::core {

    Square::Square(float side, Color color = {255,255,255}) : Shape(Shape::Geometry::Square, color), m_side(side) {
    }

    float Square::get_side_length() const noexcept {
        return m_side;
    }

} // mad::core::Square
