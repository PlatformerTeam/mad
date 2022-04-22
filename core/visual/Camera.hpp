#ifndef MAD_CORE_VISUAL_CAMERA_HPP
#define MAD_CORE_VISUAL_CAMERA_HPP

#include <visual/Renderable.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/shape/Shape.hpp>
#include "visual/image/shape/square/Square.hpp"
#include <event/management/handler/EventHandler.hpp>
#include <visual/image/static/StaticImage.hpp>
#include <visual/image/static/RenderableStatic.hpp>
#include <visual/image/animated/AnimatedImage.hpp>
#include <visual/image/animated/RenderableAnimated.hpp>
#include <visual/image/shape/square/RenderableSquare.hpp>
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
#include <set>

namespace mad::core {

    class Camera : public Renderable, public EventHandler {
    public:
        explicit Camera(Vec2d initial_position, std::shared_ptr<World> world);

        void turn_on(EventDispatcher &event_dispatcher, Entity::Id chased_id);

        void render(sf::RenderWindow &window) const override;

        void handle(const Event &event) override;

        void follow(sf::RenderWindow &window, float smoothness) const;

        void set_position(const Vec2d &position);

        void set_rotation(float angle);

        void set_zoom(float zoom);

        sf::View get_view() const noexcept;

        std::unordered_set<Event::Type> handled_types() override;

        int get_unique_number() const noexcept override;

        struct CompareScenes {
            bool operator() (const std::pair<int, std::shared_ptr<Renderable>> &a,
                             const std::pair<int, std::shared_ptr<Renderable>> &b) const;
        };

    private:
        std::set<std::pair<int, std::shared_ptr<Renderable>>, CompareScenes> m_scene_list;

        mutable Vec2d m_position;

        std::shared_ptr<World> m_world;

        std::optional<Entity::Id> m_chased_object;

        mutable sf::View m_view;
    };

}


#endif //MAD_CORE_VISUAL_CAMERA_HPP
