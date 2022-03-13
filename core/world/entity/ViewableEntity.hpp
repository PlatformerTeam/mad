#ifndef MAD_VIEWABLEENTITY_HPP
#define MAD_VIEWABLEENTITY_HPP

#include "Entity.hpp"
#include "common/FVec2D.hpp"
#include "common/Error.hpp"
#include "event/management/EventDispatcher.hpp"

namespace mad::core {
    class World;

    class Intent;

    class EventDispatcher;
}


namespace mad::core {

    class ViewableEntity : Entity{
    public:
        using Id = std::int32_t;

    public:
        void accept(World &world, Intent &intent, EventDispatcher &dispatcher) override;
        Vec2d get_image_position();
        void set_image_position(Vec2d new_position);
        void move(Vec2d move_delta);
        void appear(EventDispatcher dispatcher);

        virtual ~ViewableEntity() = default;

    private:
        const Id m_id{};
        Vec2d position;
    };

}

#endif //MAD_VIEWABLEENTITY_HPP
