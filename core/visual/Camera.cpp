#include "Camera.hpp"

#include <world/entity/ViewableEntity.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    void Camera::render_shape(sf::RenderWindow &window, const Shape &shape, Vec2d position) {
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

    void Camera::turn_on(EventDispatcher &event_dispatcher) {
        auto start_appearance = [](Entity &entity, EventDispatcher &event_dispatcher) {
            const_cast_to<ViewableEntity>(entity).appear(event_dispatcher);
        };
        m_world->manipulate(TrueFilter(), LambdaIntent(start_appearance));
    }

    void Camera::render(sf::RenderWindow &window) {
        for (const auto &[image, position] : m_scene_list) {
            switch (image->type) {
                case Image::Type::Shape: {
                    SPDLOG_INFO("Rendering shape");
                    auto shape_image = pointer_cast_to<Shape>(image);
                    render_shape(window, *shape_image, *position);
                }
            }
        }
    }

    void Camera::handle(const Event &event) {
        SPDLOG_INFO("Got positional appearance");
        const auto &positional_appearance = const_cast_to<PositionalAppearance>(event);
        m_scene_list.emplace_back(positional_appearance.get_image(), positional_appearance.get_position());
    }

    std::unordered_set<Event::Type> Camera::handled_types() {
        return {Event::Type::Visual, Event::Type::Movement};
    }

    Camera::Camera(Vec2d initial_position, std::shared_ptr<World> world)
            : m_position(initial_position),
              m_world(std::move(world)) {}

} // namespace mad::core


