#ifndef MAD_CORE_VISUAL_CAMERA_HPP
#define MAD_CORE_VISUAL_CAMERA_HPP

#include <visual/Renderable.hpp>
#include <visual/image/Image.hpp>
#include <event/management/EventHandler.hpp>
#include "event/management/dispatcher/EventDispatcher.hpp"
#include <event/visual/PositionalAppearance.hpp>
#include <world/filter/TrueFilter.hpp>
#include <world/World.hpp>
#include <world/entity/Entity.hpp>
#include <common/FVec2D.hpp>
#include <common/Error.hpp>
#include <world/intent/LambdaIntent.hpp>

#include <imgui.h>

#include <vector>

namespace mad::core {

    class Camera : public Renderable, public EventHandler {
    public:
        void turn_on(const EventDispatcher &event_dispatcher);

        void render() override;

        void handle(const Event &event) override;

    private:
        std::vector<std::pair<std::shared_ptr<Image>, std::shared_ptr<Vec2d>>> m_scene_list{};

        Vec2d m_position;

        std::shared_ptr<World> m_world;
    };

}


#endif //MAD_CORE_VISUAL_CAMERA_HPP
