#include "Camera.hpp"

namespace mad::core {

    void Camera::render_shape(sf::RenderWindow &window, const Shape &shape, Vec2d position) const {
        switch (shape.get_geometry()) {
            case Shape::Geometry::Square: {
                Square square = const_cast_to<Square>(shape);
                sf::RectangleShape render_square({square.get_side_length(), square.get_side_length()});

                Color square_color = square.get_color();

                render_square.setFillColor({square_color.get_red(),
                                            square_color.get_green(),
                                            square_color.get_blue()});

                render_square.setPosition(position.get_x(), position.get_y());
                window.draw(render_square);
            }
        }
    }

    void Camera::turn_on(const EventDispatcher &event_dispatcher) {
        auto start_appearance = [](const Entity &entity, const EventDispatcher &event_dispatcher) {
            entity.appear(event_dispatcher);
        };
        m_world->manipulate(TrueFilter(), LambdaIntent(start_appearance));
    }

    void Camera::render(sf::RenderWindow &window) {
        for (const auto &[image, position] : m_scene_list) {
            switch (image->type) {

                case Image::Type::Shape: {
                    Shape shape_image = const_cast_to<Shape>(*image);
                    render_shape(window, shape_image, *position);
                }
            }
        }

    }

    void Camera::handle(const Event &event) {
        const auto &positional_appearance = const_cast_to<PositionalAppearance>(event);
        m_scene_list.emplace_back(positional_appearance.get_image(), positional_appearance.get_position());
    }

    std::unordered_set<Event::Type> Camera::handled_types() {
        return {Event::Type::Visual, Event::Type::Movement};
    }

} // namespace mad::core


