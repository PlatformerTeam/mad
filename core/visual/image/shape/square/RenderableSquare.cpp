#include "RenderableSquare.hpp"

#include <utility>

mad::core::RenderableSquare::RenderableSquare(std::shared_ptr<Square> shape, std::shared_ptr<Vec2d> position,
                                              std::shared_ptr<float> rotation)
                                              : m_shape(shape),
                                              m_position(std::move(position)),
                                              m_rotation(std::move(rotation)){
    is_active = shape->is_active;

    m_physical_shape = sf::RectangleShape({shape->get_side_length(), shape->get_side_length()});
    m_physical_shape.setOrigin(shape->get_side_length() / 2,
                               shape->get_side_length() / 2);
    m_physical_shape.setOutlineThickness(1);
    m_physical_shape.setOutlineColor({0, 255, 0});
    m_physical_shape.setFillColor(sf::Color::Transparent);
}

bool mad::core::RenderableSquare::render(sf::RenderWindow &window) {
    Square m_square = *pointer_cast_to<Square>(m_shape);
    sf::RectangleShape render_square({m_square.get_side_length(), m_square.get_side_length()});
    render_square.setOrigin(m_square.get_side_length() / 2, m_square.get_side_length() / 2);

    Color square_color = m_square.get_color();

    render_square.setFillColor({square_color.get_red(),
                                square_color.get_green(),
                                square_color.get_blue()});


    render_square.setPosition(m_position->get_x(), m_position->get_y());
    render_square.setRotation(*m_rotation);
    window.draw(render_square);

    return true;
}

sf::RectangleShape mad::core::RenderableSquare::get_physical_shape() noexcept {
    m_physical_shape.setPosition(*m_position);
    m_physical_shape.setRotation(*m_rotation);
    return m_physical_shape;
}
