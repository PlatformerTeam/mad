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
        for (auto &renderable_image : m_scene_list) {
            renderable_image.render(window);
        }
    }

    void Camera::handle(const Event &event) {
        SPDLOG_INFO("Got positional appearance");
        const auto &positional_appearance = const_cast_to<PositionalAppearance>(event);
        RenderableImage renderable_image(positional_appearance.get_image(), positional_appearance.get_position(), positional_appearance.get_rotation());
        m_scene_list.push_back(renderable_image);
    }

    std::unordered_set<Event::Type> Camera::handled_types() {
        return {Event::Type::Visual, Event::Type::Movement};
    }

    Camera::Camera(Vec2d initial_position, std::shared_ptr<World> world)
            : m_position(initial_position),
              m_world(std::move(world)) {}

} // namespace mad::core


