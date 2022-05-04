#ifndef MAD_CAMERACONTROLLER_HPP
#define MAD_CAMERACONTROLLER_HPP

#include <event/management/controller/Controller.hpp>
#include <visual/Camera.hpp>

namespace mad::core {

    class CameraController : public Controller {
    public:
        explicit CameraController(std::shared_ptr<Camera> camera);

        void control() override;

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        std::shared_ptr<Camera> m_camera;
    };

}

#endif //MAD_CAMERACONTROLLER_HPP
