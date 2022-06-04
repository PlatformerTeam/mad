#include "EnemyStateMachine.hpp"
#include "event/management/condition/Counter.hpp"
#include "event/management/condition/EndAnimationCondition.hpp"
#include "event/management/condition/EnemyAttackCondition.hpp"
#include "event/management/condition/FallCondition.hpp"
#include "event/management/condition/KeyDownCondition.hpp"
#include "event/management/condition/KeyPressedCondition.hpp"
#include "event/management/condition/KeyReleasedCondition.hpp"
#include "event/management/condition/LastStateCondition.hpp"
#include "event/management/condition/SensorCondition.hpp"
#include "event/management/condition/SensorEndCondition.hpp"
#include "event/management/condition/TakeDamageCondition.hpp"
#include "event/management/condition/TimerCondition.hpp"
#include "event/management/condition/TrueCondition.hpp"
#include "event/management/controller/Attack.hpp"
#include "event/management/controller/Destroy.hpp"
#include "event/management/controller/Die.hpp"
#include "event/management/controller/EnemyAttack.hpp"
#include "event/management/controller/Fall.hpp"
#include "event/management/controller/FlyUp.hpp"
#include "event/management/controller/GroundMovement.hpp"
#include "event/management/controller/Hurt.hpp"
#include "event/management/controller/JumpImpulse.hpp"
#include "event/management/controller/Movement.hpp"
#include "event/management/controller/StartJump.hpp"
#include "event/management/controller/statemachine/StateMachine.hpp"

mad::core::EnemyStateMachine::EnemyStateMachine(std::shared_ptr<LocalWorld> world, mad::core::Vec2d position, int hero_id, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, float m_impulse, float horizontal_velocity, int real_hero_id)  : StateMachine(level_dispatcher){
    auto machine = this;


    StateMachine::StateId ground_idle = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId ground_idle1 = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId ground_idle2 = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId ground_right = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    StateMachine::StateId ground_left = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Left, horizontal_velocity));
    StateMachine::StateId die_idle = machine->add_state(std::make_shared<Die>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId hurt_idle = machine->add_state(std::make_shared<Hurt>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId destroy = machine->add_state(std::make_shared<Destroy>(world, level_dispatcher, hero_id));

    int *attack_stage = new int(0);
    StateMachine::StateId attack_idle = machine->add_state(std::make_shared<EnemyAttack>(world, level_dispatcher, hero_id, Movement::Direction::Idle, attack_stage, horizontal_velocity));

    machine->add_transition(ground_idle, ground_right, std::make_shared<mad::core::TimerCondition>(1 + rand() % 2));
    machine->add_transition(ground_right, ground_idle1, std::make_shared<mad::core::TimerCondition>(1 + rand() % 2));
    machine->add_transition(ground_idle1, ground_left, std::make_shared<mad::core::TimerCondition>(1 + rand() %  2));
    machine->add_transition(ground_left, ground_idle, std::make_shared<mad::core::TimerCondition>(1 + rand() % 2));

    machine->add_transition(ground_left, attack_idle, std::make_shared<mad::core::EnemyAttackCondition>(world, hero_id, real_hero_id));
    machine->add_transition(ground_idle, attack_idle, std::make_shared<mad::core::EnemyAttackCondition>(world, hero_id, real_hero_id));
    machine->add_transition(ground_idle1, attack_idle, std::make_shared<mad::core::EnemyAttackCondition>(world, hero_id, real_hero_id));

    machine->add_transition(ground_right, attack_idle, std::make_shared<mad::core::EnemyAttackCondition>(world, hero_id, real_hero_id));

    machine->add_transition(attack_idle, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_beg, attack_stage));
    machine->add_transition(attack_idle, ground_idle2, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_end, attack_stage));
    machine->add_transition(ground_idle2, ground_idle, std::make_shared<mad::core::TimerCondition>(0.7));


    machine->add_transition(ground_idle, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(ground_idle2, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(ground_idle1, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));

    machine->add_transition(ground_left, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(ground_right, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(attack_idle, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));

    int *attack_count= new int(0);

    machine->add_transition(hurt_idle, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Hurt, attack_count));

    machine->add_transition(ground_idle, die_idle, std::make_shared<mad::core::Counter>(attack_count, 3));
    machine->add_transition(ground_idle1, die_idle, std::make_shared<mad::core::Counter>(attack_count, 3));

    machine->add_transition(ground_idle2, die_idle, std::make_shared<mad::core::Counter>(attack_count, 3));

    machine->add_transition(ground_left, die_idle, std::make_shared<mad::core::Counter>(attack_count, 3));
    machine->add_transition(ground_right, die_idle, std::make_shared<mad::core::Counter>(attack_count, 3));



    machine->add_transition(die_idle, destroy, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Die));








    machine->set_initial_state(0);
    //controllers.push_back(machine);
}
