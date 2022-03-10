#include "Camera.hpp"

#include <common/Error.hpp>

namespace mad::core {

    void Camera::render() {
        NOT_IMPLEMENTED
    }

    void Camera::handle(const Event &event) {
        switch (event.type) {
            case Event::Type::Collision :
                break;
            case Event::Type::Visual :
                break;
            case Event::Type::Movement :
                break;
            case Event::Type::Keystroke:
                break;
        }
    }



} // namespace mad::core


