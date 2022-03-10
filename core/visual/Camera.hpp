#ifndef MAD_CORE_VISUAL_CAMERA_HPP
#define MAD_CORE_VISUAL_CAMERA_HPP

#include <visual/Renderable.hpp>
#include <event/management/EventHandler.hpp>
#include <world/filter/TrueFilter.hpp>
#include <world/World.hpp>
#include <visual/image/Image.hpp>
#include <common/FVec2D.hpp>

#include <vector>

namespace mad::core {

    class Camera : public Renderable, public EventHandler {
    public:
        void render() override;

        void handle(const Event &event) override;

    private:
        std::vector<std::pair<std::shared_ptr<Image>, std::shared_ptr<Vec2d>>> m_scene_list;

        Vec2d m_position;

        std::shared_ptr<World> m_world;
    };

}


#endif //MAD_CORE_VISUAL_CAMERA_HPP
