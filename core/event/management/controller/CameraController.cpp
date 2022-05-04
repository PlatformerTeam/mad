#include "CameraController.hpp"

#include <utility>

namespace mad::core {

    CameraController::CameraController(std::shared_ptr<Camera> camera) : m_camera(std::move(camera)) {
    }

    void CameraController::control() {
        m_camera->follow();
    }

    void CameraController::handle(const Event &event) {
    }

    std::unordered_set<Event::Type> CameraController::handled_types() {
        return {};
    }
}

