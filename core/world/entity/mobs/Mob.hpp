#ifndef MAD_MOB_HPP
#define MAD_MOB_HPP

#include <world/entity/PhysicalEntity.hpp>
#include <memory>

namespace mad::core {
    class World;

    class Intent;

    class EventDispatcher;
}// namespace mad::core


namespace mad::core {

    class Mob : public PhysicalEntity{
    public:
        using Id = std::int32_t;

    public:
        explicit Mob(std::string e_type, Id id, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, b2World &physicalWorld, bool is_fixed);
        //virtual void take_damage(float damage) = 0;


    private:
        float health_points{};
    };


}// namespace mad::core

#endif//MAD_MOB_HPP
