#include "Camera.hpp"

#include <world/entity/ViewableEntity.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    void Camera::turn_on(EventDispatcher &event_dispatcher, Entity::Id chased_id) {
        m_chased_object = chased_id;
        auto start_appearance = [](Entity &entity, EventDispatcher &event_dispatcher) {
            const_cast_to<ViewableEntity>(entity).appear(event_dispatcher);
        };
        m_world->manipulate(TrueFilter(), LambdaIntent(start_appearance));
    }

    void Camera::render(sf::RenderWindow &window) {
        window.setView(m_view);
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
              m_world(std::move(world)),
              m_view(initial_position, {640, 480}) {}

    void Camera::follow() {
        if (m_chased_object) {
            auto entity = cast_to<ViewableEntity>(m_world->get_entity(m_chased_object.value()));
            Vec2d position = entity.get_image_position();
            switch (m_type) {
                case FollowType::Forward: {
                    m_view.move((position - m_position) * m_smoothness);
                    m_position += (position - m_position) * m_smoothness;
                    break;
                }
                case FollowType::Backward : {
                    m_view.move((position - m_position) * m_smoothness);
                    m_position += (position - m_position) * m_smoothness;
                    break;
                }
            }
        }
    }

    sf::View Camera::get_view() const noexcept {
        return m_view;
    }

    void Camera::set_position(const Vec2d &position) {
        m_position = position;
        m_view.setCenter(m_position);
    }

    void Camera::set_rotation(float angle) {
        m_view.setRotation(angle);
    }

    void Camera::set_zoom(float zoom) {
        m_view.zoom(zoom);
    }

    void Camera::set_smoothness(float smoothness) {
        m_smoothness = smoothness;
    }

    void Camera::insert_renderable_to_scene(const std::pair<int, std::shared_ptr<Renderable>> &renderable) {
        auto position = std::upper_bound(m_scene_list.begin(), m_scene_list.end(), renderable,
                                         [](const RenderableWithIndex &a, const RenderableWithIndex &b) {
                                             return a.first < b.first;
                                         });
        m_scene_list.insert(position, renderable);
    }

    void Camera::set_follow_type(Camera::FollowType type) {
        m_type = type;
    }

} // namespace mad::core


