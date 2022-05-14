#include "RenderableSquare.hpp"

#include <utility>

mad::core::RenderableSquare::RenderableSquare(std::shared_ptr<Shape> shape,
                                              std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation)
                                              : m_shape(shape),
                                              m_position(std::move(position)),
                                              m_rotation(std::move(rotation)) {
    is_active = shape->is_active;
    is_reflect = shape->is_reflect;
}

void mad::core::RenderableSquare::render(sf::RenderWindow &window) {
    Square m_square = *pointer_cast_to<Square>(m_shape);
    sf::RectangleShape render_square({m_square.get_side_length(), m_square.get_side_length()});
    render_square.setOrigin(m_square.get_side_length() / 2, m_square.get_side_length() / 2);

    Color square_color = m_square.get_color();

    if (*is_reflect) {
        render_square.setScale(-1, -1);
    }

    render_square.setFillColor({square_color.get_red(),
                                square_color.get_green(),
                                square_color.get_blue()});


    render_square.setPosition(m_position->get_x(), m_position->get_y());
    render_square.setRotation(*m_rotation);
    window.draw(render_square);
}
