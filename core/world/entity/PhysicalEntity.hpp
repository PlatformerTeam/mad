#ifndef MAD_PHYSICALENTITY_HPP
#define MAD_PHYSICALENTITY_HPP

#include "Entity.hpp"
#include "ViewableEntity.hpp"

#include <box2d/box2d.h>
#include <common/Error.hpp>
#include <common/FVec2D.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/shape/Shape.hpp>


#include <memory>

namespace mad::core {
    class World;

    class Intent;

    class EventDispatcher;
}// namespace mad::core


namespace mad::core {

    class PhysicalEntity : public ViewableEntity {
    public:
        using Id = std::int32_t;

    public:
        explicit PhysicalEntity(Id id, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, b2World &physicalWorld, bool is_fixed);

        void accept(World &world, const Intent &intent, EventDispatcher &dispatcher) override;

        void apply_impulse(Vec2d impulse, EventDispatcher &dispatcher);
        void apply_force(Vec2d impulse, EventDispatcher &dispatcher);

        void rotate(float angle, EventDispatcher &dispatcher);

        void synchronize_position_with_viewable();


    private:
        b2Body *body;
    };


}// namespace mad::core

#endif//MAD_PHYSICALENTITY_HPP
