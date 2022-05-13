#ifndef MAD_CORE_VISUAL_CAMERA_HPP
#define MAD_CORE_VISUAL_CAMERA_HPP

#include <visual/Renderable.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/shape/Shape.hpp>
#include <visual/image/shape/square/Square.hpp>
#include <event/management/handler/EventHandler.hpp>
#include <visual/image/static/StaticImage.hpp>
#include <visual/image/static/RenderableStatic.hpp>
#include <visual/image/animated/AnimatedImageOneFile.hpp>
#include <visual/image/animated/AnimatedImageSeveralFiles.hpp>
#include <visual/image/animated/RenderableAnimatedOneFile.hpp>
#include <visual/image/animated/RenderableAnimatedSeveralFiles.hpp>
#include <visual/image/animated/AnimatedImageSeveralFiles.hpp>
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
    private:
        using RenderableWithIndex = std::pair<int, std::shared_ptr<Renderable>>;

    public:
        enum class FollowType {
            Forward,
            Backward
        };

        explicit Camera(Vec2d initial_position, std::shared_ptr<World> world);

        void turn_on(EventDispatcher &event_dispatcher, Entity::Id chased_id);

        void render(sf::RenderWindow &window) override;

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

        void follow();

        sf::View get_view() const noexcept;

        void set_position(const Vec2d &position);

        void set_rotation(float angle);

        void set_zoom(float zoom);

        void set_smoothness(float smoothness);

        void set_follow_type(FollowType type, float minimal_distant);

    private:
        void insert_renderable_to_scene(const std::pair<int, std::shared_ptr<Renderable>> &renderable);

        std::vector<std::pair<int, std::shared_ptr<Renderable>>> m_scene_list;

        std::optional<Entity::Id> m_chased_object;

        sf::View m_view;

        Vec2d m_position;

        std::optional<Vec2d> m_last_position;

        std::shared_ptr<World> m_world;

        float m_smoothness = 0.5;

        FollowType m_type = FollowType::Backward;

        float m_minimal_distant = 1.0f;
    };

}


#endif //MAD_CORE_VISUAL_CAMERA_HPP
