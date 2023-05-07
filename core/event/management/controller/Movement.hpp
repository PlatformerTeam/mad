#ifndef MAD_MOVEMENT_HPP
#define MAD_MOVEMENT_HPP


#include "Controller.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class Movement : public Controller {
    public:
        enum class Direction {
            Right,
            Left,
            Idle,
        };
        explicit Movement(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir, float velocity = 0);

        void control() override;

    private:
        std::shared_ptr<mad::core::LocalWorld> m_world;
        Entity::Id m_entity_id;
        Direction dir;
        PhysicalEntity* m_entity;
        float velocity;
    protected:
        ImageStorage::TypeAction Move_animation;
        ImageStorage::TypeAction Idle_animation;
    };

}

#endif//MAD_MOVEMENT_HPP
