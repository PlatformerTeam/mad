#ifndef MAD_VIEWABLEENTITY_HPP
#define MAD_VIEWABLEENTITY_HPP

#include "Entity.hpp"
#include "common/FVec2D.hpp"
#include "common/Error.hpp"
#include "visual/image/Image.hpp"
#include "event/management/dispatcher/EventDispatcher.hpp"
#include <visual/image/shape/Shape.hpp>


#include <memory>

namespace mad::core {
    class World;

    class Intent;

    class EventDispatcher;
}


namespace mad::core {

    class ViewableEntity : public Entity {
    public:
        using Id = std::int32_t;

    public:
        explicit ViewableEntity(Entity::Type e_type, Id id, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image);

        void accept(World &world, const Intent &intent, EventDispatcher &dispatcher) override;

        Vec2d get_image_position();

        void set_image_position(Vec2d new_position);

        void set_image_rotation(float new_rotation);

        void set_image_color(Color color);

        void move(Vec2d move_delta);

        void appear(EventDispatcher &dispatcher) const;

    protected:
        const Id m_id;

        int m_z_ind;

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

        std::shared_ptr<Image> m_image;
    };

}

#endif //MAD_VIEWABLEENTITY_HPP
