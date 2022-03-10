#include "Camera.hpp"

namespace mad::core {

    void Camera::turn_on(const EventDispatcher &event_dispatcher) {
        auto start_appearance = [](const Entity &entity, const EventDispatcher &event_dispatcher) {
            NOT_IMPLEMENTED // entity.appear(event_dispatcher);
        };
        m_world->manipulate(TrueFilter(), LambdaIntent(start_appearance));
    }

    void Camera::render() {
        NOT_IMPLEMENTED

    }

    void Camera::handle(const Event &event) {
        const PositionalAppearance &positional_appearance = static_cast<const PositionalAppearance&>(event);
        m_scene_list.emplace_back(positional_appearance.get_image(), positional_appearance.get_position());
    }



} // namespace mad::core


