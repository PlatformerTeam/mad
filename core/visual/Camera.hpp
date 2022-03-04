#ifndef MAD_CORE_VISUAL_CAMERA_HPP
#define MAD_CORE_VISUAL_CAMERA_HPP

#include <visual/Renderable.hpp>


namespace mad::core {

    class Camera : public Renderable {
    public:
        void render() override;
    };

}


#endif //MAD_CORE_VISUAL_CAMERA_HPP
