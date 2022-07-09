#ifndef MAD_HEROSTATEMACHINE_HPP
#define MAD_HEROSTATEMACHINE_HPP

#include "StateMachine.hpp"
#include "world/LocalWorld.hpp"
namespace mad::core {
    class HeroStateMachine : public StateMachine {

    public:
        explicit HeroStateMachine(std::shared_ptr<LocalWorld> world, Vec2d position, int hero_id, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, float m_impulse, float horizontal_velocity);
    private:
        float health = 30;

    };

}// namespace mad::core


#endif//MAD_HEROSTATEMACHINE_HPP
