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

    void Camera::render(sf::RenderWindow &window) const {
        follow(window, 0.02f);
        for (auto &[z_ind, renderable_image] : m_scene_list) {
            renderable_image->render(window);
        }
    }

    void Camera::handle(const Event &event) {
        SPDLOG_INFO("Got positional appearance");
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
                        m_scene_list.insert({positional_appearance.get_z_index(),
                                             std::make_shared<RenderableSquare>(renderable_square)});
                        break;
                }
                break;
            }
            case Image::Type::Static: {
                std::shared_ptr<StaticImage> static_image = pointer_cast_to<StaticImage>(positional_appearance.get_image());
                RenderableStatic renderable_static(static_image,
                                                   positional_appearance.get_position(),
                                                   positional_appearance.get_rotation());
                m_scene_list.insert({positional_appearance.get_z_index(),
                                     std::make_shared<RenderableStatic>(renderable_static)});
                break;
            }
            case Image::Type::Animated:
                std::shared_ptr<AnimatedImage> animated_image = pointer_cast_to<AnimatedImage>(positional_appearance.get_image());
                RenderableAnimated renderable_animated(animated_image,
                                                   positional_appearance.get_position(),
                                                   positional_appearance.get_rotation());
                m_scene_list.insert({positional_appearance.get_z_index(),
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
              m_view(m_position, {640, 480}) {}

              // TODO: replace follow to controller
    void Camera::follow(sf::RenderWindow &window, float smoothness) const {
        if (m_chased_object) {
            auto entity = cast_to<ViewableEntity>(m_world->get_entity(m_chased_object.value()));
            Vec2d position = entity.get_image_position();
            m_view.move((position - m_position) * smoothness);
            m_position += (position - m_position) * smoothness;
        }
        window.setView(m_view);
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

    int Camera::get_unique_number() const noexcept {
        return 0;
    }

    bool Camera::CompareScenes::operator()(const std::pair<int, std::shared_ptr<Renderable>> &a,
                                           const std::pair<int, std::shared_ptr<Renderable>> &b) const {
        return a.first == b.first ? a.second->get_unique_number() < b.second->get_unique_number()
        : a.first < b.first;
    }

} // namespace mad::core


