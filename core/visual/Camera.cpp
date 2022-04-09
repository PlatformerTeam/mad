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

    void Camera::render(sf::RenderWindow &window) const {
        for (auto &[z_ind, renderable_image] : m_scene_list) {
            renderable_image.render(window);
        }
    }

    void Camera::handle(const Event &event) {
        SPDLOG_INFO("Got positional appearance");
        const auto &positional_appearance = const_cast_to<PositionalAppearance>(event);
        RenderableImage renderable_image(positional_appearance.get_image(), positional_appearance.get_position(), positional_appearance.get_rotation());
        m_scene_list.insert({positional_appearance.get_z_index(), renderable_image});
    }

    std::unordered_set<Event::Type> Camera::handled_types() {
        return {Event::Type::Visual, Event::Type::Movement};
    }

    Camera::Camera(Vec2d initial_position, std::shared_ptr<World> world)
            : m_position(initial_position),
              m_world(std::move(world)) {}

    bool Camera::compareScenes::operator()(const std::pair<int, RenderableImage> &a,
                                           const std::pair<int, RenderableImage> &b) const {
        return a.first == b.first ? a.second.get_unique_number() < b.second.get_unique_number()
        : a.first < b.first;
    }

} // namespace mad::core


