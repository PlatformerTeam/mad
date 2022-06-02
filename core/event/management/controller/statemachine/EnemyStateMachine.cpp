#include "EnemyStateMachine.hpp"
#include "event/management/condition/EndAnimationCondition.hpp"
#include "event/management/condition/FallCondition.hpp"
#include "event/management/condition/KeyDownCondition.hpp"
#include "event/management/condition/KeyPressedCondition.hpp"
#include "event/management/condition/KeyReleasedCondition.hpp"
#include "event/management/condition/LastStateCondition.hpp"
#include "event/management/condition/SensorCondition.hpp"
#include "event/management/condition/SensorEndCondition.hpp"
#include "event/management/condition/TimerCondition.hpp"
#include "event/management/condition/TrueCondition.hpp"
#include "event/management/controller/Attack.hpp"
#include "event/management/controller/Fall.hpp"
#include "event/management/controller/FlyUp.hpp"
#include "event/management/controller/GroundMovement.hpp"
#include "event/management/controller/JumpImpulse.hpp"
#include "event/management/controller/Movement.hpp"
#include "event/management/controller/StartJump.hpp"
#include "event/management/controller/statemachine/StateMachine.hpp"

mad::core::EnemyStateMachine::EnemyStateMachine(std::shared_ptr<LocalWorld> world, mad::core::Vec2d position, int hero_id, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, float m_impulse, float horizontal_velocity)  : StateMachine(level_dispatcher){
    auto machine = this;


    StateMachine::StateId ground_idle = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId ground_right = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    StateMachine::StateId ground_left = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Left, horizontal_velocity));
    int *attack_stage = new int(0);
    StateMachine::StateId attack_idle= machine->add_state(std::make_shared<Attack>(world, hero_id, Movement::Direction::Idle, attack_stage, horizontal_velocity));

    machine->add_transition(ground_idle, ground_right, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(ground_idle, ground_left, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(ground_right, ground_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));
    machine->add_transition(ground_left, ground_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(ground_right, ground_left, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(ground_left, ground_right, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));


    machine->add_transition(ground_left, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(ground_idle, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(ground_right, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));

    machine->add_transition(attack_idle, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_beg, attack_stage));
    machine->add_transition(attack_idle, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_end, attack_stage));










    machine->set_initial_state(0);
    //controllers.push_back(machine);
}
