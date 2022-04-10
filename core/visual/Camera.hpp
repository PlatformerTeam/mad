#ifndef MAD_CORE_VISUAL_CAMERA_HPP
#define MAD_CORE_VISUAL_CAMERA_HPP

#include <visual/Renderable.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/shape/Shape.hpp>
#include <visual/image/shape/Square.hpp>
#include <event/management/handler/EventHandler.hpp>
#include <visual/image/static/StaticImage.hpp>
#include <visual/image/RenderableImage.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/visual/PositionalAppearance.hpp>
#include <world/filter/TrueFilter.hpp>
#include <world/World.hpp>
#include <world/entity/Entity.hpp>
#include <common/FVec2D.hpp>
#include <common/Error.hpp>
#include <world/intent/LambdaIntent.hpp>
#include <common/Cast.hpp>

#include <SFML/Graphics.hpp>

#include <vector>
#include <optional>

namespace mad::core {

    class Camera : public Renderable, public EventHandler {
    public:
        explicit Camera(Vec2d initial_position, std::shared_ptr<World> world);

        void turn_on(EventDispatcher &event_dispatcher);

        void render(sf::RenderWindow &window) override;

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        std::vector<RenderableImage> m_scene_list;

        Vec2d m_position;

        std::shared_ptr<World> m_world;
    };

}


#endif //MAD_CORE_VISUAL_CAMERA_HPP
