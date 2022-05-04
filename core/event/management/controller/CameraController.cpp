#include "CameraController.hpp"

#include <utility>

namespace mad::core {

    CameraController::CameraController(std::shared_ptr<Camera> camera) : m_camera(std::move(camera)) {
    }

    void CameraController::control() {
        m_camera->follow();
    }
}

