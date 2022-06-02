#ifndef MAD_ENEMYSTATEMACHINE_HPP
#define MAD_ENEMYSTATEMACHINE_HPP

#include "StateMachine.hpp"
#include "world/LocalWorld.hpp"
namespace mad::core{
    class EnemyStateMachine : public StateMachine {

    public:
        explicit EnemyStateMachine(std::shared_ptr<LocalWorld> world, Vec2d position, int hero_id, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, float m_impulse, float horizontal_velocity);
    };
}


#endif//MAD_ENEMYSTATEMACHINE_HPP
