#include "Camera.hpp"

#include <world/entity/ViewableEntity.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    void Camera::turn_on(EventDispatcher &event_dispatcher) {
        auto start_appearance = [](Entity &entity, EventDispatcher &event_dispatcher) {
            const_cast_to<ViewableEntity>(entity).appear(event_dispatcher);
        };
        m_world->manipulate(TrueFilter(), LambdaIntent(start_appearance));
    }

    void Camera::render(sf::RenderWindow &window) {
        for (auto &[z_ind, renderable_image] : m_scene_list) {
            renderable_image->render(window);
        }
    }

    void Camera::handle(const Event &event) {
        SPDLOG_DEBUG("Got positional appearance");
        const auto &positional_appearance = const_cast_to<PositionalAppearance>(event);
        std::shared_ptr<Image> image = positional_appearance.get_image();
        switch (image->type) {

            case Image::Type::Shape: {
                std::shared_ptr<Shape> shape = pointer_cast_to<Shape>(image);

                switch (shape->get_geometry()) {
                    case Shape::Geometry::Square:
                        std::shared_ptr<Square> square = pointer_cast_to<Square>(shape);
                        RenderableSquare renderable_square(square,
                                                           positional_appearance.get_position(),
                                                           positional_appearance.get_rotation());
                        insert_renderable_to_scene({positional_appearance.get_z_index(),
                                                    std::make_shared<RenderableSquare>(renderable_square)});
                        break;
                }
                break;
            }
            case Image::Type::Static: {
                std::shared_ptr<StaticImage> static_image = pointer_cast_to<StaticImage>(
                        positional_appearance.get_image());
                RenderableStatic renderable_static(static_image,
                                                   positional_appearance.get_position(),
                                                   positional_appearance.get_rotation());
                insert_renderable_to_scene({positional_appearance.get_z_index(),
                                            std::make_shared<RenderableStatic>(renderable_static)});
                break;
            }
            case Image::Type::Animated:
                std::shared_ptr<AnimatedImage> animated_image = pointer_cast_to<AnimatedImage>(
                        positional_appearance.get_image());
                RenderableAnimated renderable_animated(animated_image,
                                                       positional_appearance.get_position(),
                                                       positional_appearance.get_rotation());
                insert_renderable_to_scene({positional_appearance.get_z_index(),
                                            std::make_shared<RenderableAnimated>(renderable_animated)});
                break;
        }
    }

    std::unordered_set<Event::Type> Camera::handled_types() {
        return {Event::Type::Visual, Event::Type::Movement};
    }

    Camera::Camera(Vec2d initial_position, std::shared_ptr<World> world)
            : m_position(initial_position),
              m_world(std::move(world)) {}

    void Camera::insert_renderable_to_scene(const std::pair<int, std::shared_ptr<Renderable>> &renderable) {
        auto position = std::upper_bound(m_scene_list.begin(), m_scene_list.end(), renderable,
                                         [](const RenderableWithIndex &a, const RenderableWithIndex &b) {
                                             return a.first < b.first;
                                         });
        m_scene_list.insert(position, renderable);
    }

} // namespace mad::core
