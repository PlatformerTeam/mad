#include "HeroStateMachine.hpp"
#include "event/management/condition/Counter.hpp"
#include "event/management/condition/EndAnimationCondition.hpp"
#include "event/management/condition/FallCondition.hpp"
#include "event/management/condition/FallDownCondition.hpp"
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
#include "event/management/controller/DealDamage.hpp"
#include "event/management/controller/Destroy.hpp"
#include "event/management/controller/Die.hpp"
#include "event/management/controller/Fall.hpp"
#include "event/management/controller/FlyUp.hpp"
#include "event/management/controller/GroundMovement.hpp"
#include "event/management/controller/Hurt.hpp"
#include "event/management/controller/JumpImpulse.hpp"
#include "event/management/controller/Movement.hpp"
#include "event/management/controller/StartJump.hpp"
#include "event/management/controller/statemachine/StateMachine.hpp"

mad::core::HeroStateMachine::HeroStateMachine(std::shared_ptr<LocalWorld> world, mad::core::Vec2d position, int hero_id, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, float m_impulse, float horizontal_velocity)  : StateMachine(level_dispatcher){
    auto machine = this;


    StateMachine::StateId ground_idle = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId ground_right = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    StateMachine::StateId ground_left = machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Left, horizontal_velocity));
    StateMachine::StateId jump_impulse = machine->add_state(std::make_shared<JumpImpulse>(world, hero_id, m_impulse));
    StateMachine::StateId start_jump_left = machine->add_state(std::make_shared<StartJump>(world, hero_id, Movement::Direction::Left, horizontal_velocity));
    StateMachine::StateId start_jump_idle = machine->add_state(std::make_shared<StartJump>(world, hero_id, Movement::Direction::Idle, horizontal_velocity));
    StateMachine::StateId start_jump_right = machine->add_state(std::make_shared<StartJump>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    StateMachine::StateId fly_up_left = machine->add_state(std::make_shared<FlyUp>(world, hero_id, Movement::Direction::Left, horizontal_velocity)); /// 7
    StateMachine::StateId fly_up_idle = machine->add_state(std::make_shared<FlyUp>(world, hero_id, Movement::Direction::Idle, horizontal_velocity));
    StateMachine::StateId fly_up_right = machine->add_state(std::make_shared<FlyUp>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    StateMachine::StateId fall_left = machine->add_state(std::make_shared<Fall>(world, hero_id, Movement::Direction::Left, horizontal_velocity)); /// 10
    StateMachine::StateId fall_idle = machine->add_state(std::make_shared<Fall>(world, hero_id, Movement::Direction::Idle, horizontal_velocity));
    StateMachine::StateId fall_right= machine->add_state(std::make_shared<Fall>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    int *attack_stage = new int(0);
    int *attack_count= new int(0);
    StateMachine::StateId attack_left = machine->add_state(std::make_shared<Attack>(world, level_dispatcher, hero_id, Movement::Direction::Left,  attack_stage, horizontal_velocity));
    StateMachine::StateId attack_idle= machine->add_state(std::make_shared<Attack>(world, level_dispatcher, hero_id, Movement::Direction::Idle, attack_stage, horizontal_velocity));
    StateMachine::StateId attack_right = machine->add_state(std::make_shared<Attack>(world, level_dispatcher, hero_id, Movement::Direction::Right, attack_stage, horizontal_velocity));
    StateMachine::StateId deal_damage = machine->add_state(std::make_shared<DealDamage>(world, hero_id, level_dispatcher));
    StateMachine::StateId hurt_idle = machine->add_state(std::make_shared<Hurt>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId die_idle = machine->add_state(std::make_shared<Die>(world, hero_id, Movement::Direction::Idle));
    StateMachine::StateId destroy = machine->add_state(std::make_shared<Destroy>(world, level_dispatcher, hero_id));


    machine->add_transition(ground_idle, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(ground_left, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(ground_right, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(attack_idle, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(attack_left, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(attack_right, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(fall_idle, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(fall_left, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(fall_right, hurt_idle, std::make_shared<mad::core::TakeDamageCondition>(hero_id));
    machine->add_transition(hurt_idle, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Hurt, attack_count));

    machine->add_transition(ground_idle, die_idle, std::make_shared<mad::core::Counter>(attack_count, 5));
    machine->add_transition(ground_left, die_idle, std::make_shared<mad::core::Counter>(attack_count, 5));
    machine->add_transition(ground_right, die_idle, std::make_shared<mad::core::Counter>(attack_count, 5));

    machine->add_transition(fall_idle, die_idle, std::make_shared<mad::core::FallDownCondition>(world, hero_id));
    machine->add_transition(fall_left, die_idle, std::make_shared<mad::core::FallDownCondition>(world, hero_id));
    machine->add_transition(fall_right, die_idle, std::make_shared<mad::core::FallDownCondition>(world, hero_id));



    machine->add_transition(die_idle, destroy, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Die));
    machine->add_transition(destroy, ground_idle, std::make_shared<mad::core::TrueCondition>());








    machine->add_transition(ground_idle, ground_right, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(ground_idle, ground_left, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(ground_right, ground_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));
    machine->add_transition(ground_left, ground_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(ground_right, ground_left, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(ground_left, ground_right, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(ground_idle, jump_impulse, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));
    machine->add_transition(ground_right, jump_impulse, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));
    machine->add_transition(ground_left, jump_impulse, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));

    machine->add_transition(jump_impulse, start_jump_idle, std::make_shared<TrueCondition>());
    machine->add_transition(start_jump_idle, start_jump_left , std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(start_jump_idle, start_jump_right, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(start_jump_left , start_jump_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(start_jump_right, start_jump_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));


    machine->add_transition(start_jump_left , fly_up_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Jump));
    machine->add_transition(start_jump_idle, fly_up_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Jump));
    machine->add_transition(start_jump_right, fly_up_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Jump));

    machine->add_transition(fly_up_idle, fly_up_left, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(fly_up_idle, fly_up_right, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(fly_up_left, fly_up_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(fly_up_right, fly_up_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));

    machine->add_transition(fly_up_left, fall_idle, std::make_shared<mad::core::FallCondition>(world, hero_id, 0));
    machine->add_transition(fly_up_idle, fall_idle, std::make_shared<mad::core::FallCondition>(world, hero_id, 0));
    machine->add_transition(fly_up_right, fall_idle, std::make_shared<mad::core::FallCondition>(world, hero_id, 0));

    machine->add_transition(ground_left, fall_idle, std::vector<std::shared_ptr<mad::core::Condition>>{std::make_shared<mad::core::FallCondition>(world, hero_id, 0.1), std::make_shared<mad::core::SensorEndCondition>(hero_id, 0.2)});
    machine->add_transition(ground_idle, fall_idle, std::vector<std::shared_ptr<mad::core::Condition>>{std::make_shared<mad::core::FallCondition>(world, hero_id, 0.1), std::make_shared<mad::core::SensorEndCondition>(hero_id, 0.2)});
    machine->add_transition(ground_right, fall_idle, std::vector<std::shared_ptr<mad::core::Condition>>{std::make_shared<mad::core::FallCondition>(world, hero_id, 0.1), std::make_shared<mad::core::SensorEndCondition>(hero_id, 0.2)});

    machine->add_transition(fall_idle, fall_left, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(fall_idle, fall_right, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(fall_left, fall_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(fall_right, fall_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));

    machine->add_transition(fall_left, ground_idle, std::make_shared<mad::core::SensorCondition>(hero_id));
    machine->add_transition(fall_idle, ground_idle, std::make_shared<mad::core::SensorCondition>(hero_id));
    machine->add_transition(fall_right, ground_idle, std::make_shared<mad::core::SensorCondition>(hero_id));


    machine->add_transition(ground_left, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(ground_idle, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(ground_right, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(start_jump_left, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(start_jump_idle, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(start_jump_right, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(fly_up_left, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(fly_up_idle, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(fly_up_right, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(fall_left, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(fall_idle, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));
    machine->add_transition(fall_right, attack_idle, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Q));

    machine->add_transition(attack_idle, attack_left, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(attack_left, attack_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(attack_idle, attack_right, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(attack_right, attack_idle, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));

    machine->add_transition(attack_idle, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_beg, attack_stage));
    machine->add_transition(attack_left, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_beg, attack_stage));
    machine->add_transition(attack_right, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_beg, attack_stage));

    machine->add_transition(attack_left, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_end, attack_stage));
    machine->add_transition(attack_idle, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_end, attack_stage));
    machine->add_transition(attack_right, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_1_end, attack_stage));

    machine->add_transition(attack_idle, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_2_beg, attack_stage));
    machine->add_transition(attack_left, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_2_beg, attack_stage));
    machine->add_transition(attack_right, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_2_beg, attack_stage));

    machine->add_transition(attack_left, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_2_end, attack_stage));
    machine->add_transition(attack_idle, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_2_end, attack_stage));
    machine->add_transition(attack_right, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_2_end, attack_stage));

    machine->add_transition(attack_idle, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_3_beg, attack_stage));
    machine->add_transition(attack_left, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_3_beg, attack_stage));
    machine->add_transition(attack_right, attack_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_3_beg, attack_stage));

    machine->add_transition(attack_left, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_3_end, attack_stage));
    machine->add_transition(attack_idle, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_3_end, attack_stage));
    machine->add_transition(attack_right, ground_idle, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Attack_3_end, attack_stage));








    machine->set_initial_state(0);
    //controllers.push_back(machine);
}
