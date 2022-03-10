#include "Shape.hpp"

namespace mad::core {

    Shape::Geometry Shape::get_geometry() const noexcept {
        return m_geometry;
    }

    Color Shape::get_color() const noexcept {
        return m_color;
    }

    Shape::Shape(Geometry geometry, Color color) : Image(Image::Type::Shape), m_geometry(geometry), m_color(color) {
    }

}// namespace mad::core
