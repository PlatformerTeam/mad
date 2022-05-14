#ifndef MAD_RUN_HPP
#define MAD_RUN_HPP
#include "Controller.hpp"
#include "world/LocalWorld.hpp"
#include "world/World.hpp"

namespace mad::core {

    class Run : public Controller {
    public:
        enum class Direction {
            Right,
            Left,
        };
        explicit Run(std::shared_ptr<mad::core::LocalWorld> world, Entity::Id entity_id, Direction dir);

        void control() override;

    private:
        std::shared_ptr<mad::core::LocalWorld> m_world;
        Entity::Id m_entity_id;
        Direction dir;
        PhysicalEntity* m_entity;

    };

}

#endif//MAD_RUN_HPP
