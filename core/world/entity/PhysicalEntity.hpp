#ifndef MAD_PHYSICALENTITY_HPP
#define MAD_PHYSICALENTITY_HPP

#include "Entity.hpp"
#include "ViewableEntity.hpp"

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/shape/Shape.hpp>

#include <common/Error.hpp>
#include <common/FVec2D.hpp>

#include <box2d/box2d.h>

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
        explicit PhysicalEntity(Id id, int z_ind, Vec2d initial_position, float initial_rotation,
                                std::shared_ptr<ImageStorage> image_storage,
                                b2World &physicalWorld, bool is_fixed, bool is_rotated);

        void accept(World &world, const Intent &intent, EventDispatcher &dispatcher) override;

        void set_transform(Vec2d position, float angle);
        void apply_linear_impulse(Vec2d impulse, Vec2d point, EventDispatcher &dispatcher, bool awake = true);
        void apply_linear_impulse_to_center(Vec2d impulse, EventDispatcher &dispatcher, bool awake = true);
        void apply_force(Vec2d force, Vec2d point, EventDispatcher &dispatcher, bool awake = true);
        void apply_force_to_center(Vec2d force, EventDispatcher &dispatcher, bool awake = true);
        void apply_angular_impulse(float impulse, EventDispatcher &dispatcher, bool awake = true);
        void apply_torque(float torque, EventDispatcher &dispatcher, bool awake = true);
        void set_linear_velocity(Vec2d velocity, EventDispatcher &dispatcher);
        void set_linear_horizontal_velocity(float velocity, EventDispatcher &dispatcher);
        void set_angular_velocity(float velocity, EventDispatcher &dispatcher);
        void set_linear_damping(float linear_damping, EventDispatcher &dispatcher);
        void set_angular_damping(float angular_damping, EventDispatcher &dispatcher);
        void set_gravity_scale(float gravity_scale, EventDispatcher &dispatcher);


        Vec2d get_position();
        float get_angle();
        float get_mass();
        float get_inertia();
        Vec2d get_linear_velocity();
        float get_angular_velocity();
        float get_linear_damping();
        float get_angular_damping();
        float get_gravity_scale();

        bool is_bullet();
        void set_bullet(bool flag);
        bool is_awake();
        void set_awake(bool flag);
        bool is_enabled();
        void set_enabled(bool flag);
        bool is_fixed_rotation();
        void set_fixed_rotation(bool flag);

        Vec2d get_local_center();
        Vec2d get_world_center();


        void rotate(float angle, EventDispatcher &dispatcher);

        void synchronize_position_with_viewable();

        void add_sensor(b2Vec2 offset, float x_size, float y_size);


    private:
        b2Body *body;
    };


}// namespace mad::core

#endif//MAD_PHYSICALENTITY_HPP
