#include "Camera.hpp"

#include <world/entity/ViewableEntity.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    void Camera::render_shape(sf::RenderWindow &window, const Shape &shape, Vec2d position, float rotation) {
        switch (shape.get_geometry()) {
            case Shape::Geometry::Square: {
                Square square = const_cast_to<Square>(shape);
                sf::RectangleShape render_square({square.get_side_length(), square.get_side_length()});
                render_square.setOrigin(square.get_side_length() / 2, square.get_side_length() / 2);

                Color square_color = square.get_color();

                render_square.setFillColor({square_color.get_red(),
                                            square_color.get_green(),
                                            square_color.get_blue()});


                render_square.setPosition(position.get_x(), position.get_y());
                render_square.setRotation(rotation);
                window.draw(render_square);
            }
        }
    }

    void Camera::render_static(sf::RenderWindow &window, const StaticImage &static_image, Vec2d position, float rotation) {

        sf::Sprite render_sprite;
        sf::Texture texture;

        texture = static_image.get_texture();
        render_sprite.setTexture(texture);

        render_sprite.setScale(static_image.get_scale().get_x(), static_image.get_scale().get_y());

        render_sprite.setPosition(position.get_x(), position.get_y());

        if (static_image.get_rect()) {
            render_sprite.setTextureRect(static_image.get_rect().value());
        }

        render_sprite.setRotation(0.5);

        window.draw(render_sprite);
    }

    void Camera::turn_on(EventDispatcher &event_dispatcher) {
        auto start_appearance = [](Entity &entity, EventDispatcher &event_dispatcher) {
            const_cast_to<ViewableEntity>(entity).appear(event_dispatcher);
        };
        m_world->manipulate(TrueFilter(), LambdaIntent(start_appearance));
    }

    void Camera::render(sf::RenderWindow &window) {
        for (const auto &[image, position, rotation] : m_scene_list) {
            switch (image->type) {
                case Image::Type::Shape: {
                    auto shape_image = pointer_cast_to<Shape>(image);
                    render_shape(window, *shape_image, *position, *rotation);
                    break;
                }
                case Image::Type::Static:
                    auto static_image = pointer_cast_to<StaticImage>(image);
                    render_static(window, *static_image, *position, *rotation);
                    break;
            }
        }
    }

    void Camera::handle(const Event &event) {
        SPDLOG_INFO("Got positional appearance");
        const auto &positional_appearance = const_cast_to<PositionalAppearance>(event);
        m_scene_list.push_back({positional_appearance.get_image(), positional_appearance.get_position(), positional_appearance.get_rotation()});
    }

    std::unordered_set<Event::Type> Camera::handled_types() {
        return {Event::Type::Visual, Event::Type::Movement};
    }

    Camera::Camera(Vec2d initial_position, std::shared_ptr<World> world)
            : m_position(initial_position),
              m_world(std::move(world)) {}

} // namespace mad::core


