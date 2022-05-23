#include "Hero.hpp"
#include "event/management/condition/EndAnimationCondition.hpp"
#include "event/management/condition/FallCondition.hpp"
#include "event/management/condition/KeyDownCondition.hpp"
#include "event/management/condition/KeyPressedCondition.hpp"
#include "event/management/condition/KeyReleasedCondition.hpp"
#include "event/management/condition/LastStateCondition.hpp"
#include "event/management/condition/SensorCondition.hpp"
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
mad::core::Hero::Hero(std::shared_ptr<LocalWorld> world, Vec2d position, json m_config_json, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, std::vector<std::shared_ptr<mad::core::Controller>> &controllers) : level_dispatcher(level_dispatcher){
    std::filesystem::path source(m_config_json["animated_resources"]);
    source /= m_config_json["hero"]["source"];

    std::shared_ptr<ImageStorage> image_storage;

    float physical_size_width = m_config_json["hero"]["animated"]["size_width"];
    float physical_size_height = m_config_json["hero"]["animated"]["size_height"];
    float size_scale = m_config_json["hero"]["animated"]["size_scale"];
    float delta_x = m_config_json["hero"]["animated"]["delta_x"];
    float delta_y = m_config_json["hero"]["animated"]["delta_y"];


    image_storage = std::make_shared<ImageStorage>(
            std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                    {{ImageStorage::TypeAction::Idle,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["idle"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["idle"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Run,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["run"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["run"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Jump,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["jump"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["jump"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Fly_up,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["fly_up"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["fly_up"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Fall,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["fall"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["fall"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Attack_1_beg,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["attack_1_beg"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["attack_1_beg"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Attack_1_end,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["attack_1_end"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["attack_1_end"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Attack_2_beg,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["attack_2_beg"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["attack_2_beg"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Attack_2_end,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["attack_2_end"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["attack_2_end"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Attack_3_beg,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["attack_3_beg"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["attack_3_beg"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)},
                     {ImageStorage::TypeAction::Attack_3_end,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["attack_3_end"]["source"],

                              m_config_json["hero"]["animated"]["actions"]["attack_3_end"]["delta_time"],
                              physical_size_width, physical_size_height, size_scale,
                              delta_x, delta_y)}
                    }
                    ));

    hero_id = world->create_physical_entity(
            0,
            position,
            0,
            image_storage,
            false, false
    );


    ///State Machine
    struct C1 : mad::core::Controller {
        void control() override {
                //SPDLOG_DEBUG("controller 1");
        };
    };
    struct C2 : mad::core::Controller {
        void control() override {
                //SPDLOG_DEBUG("controller 2");
        };
    };
    auto machine = std::make_shared<mad::core::StateMachine>(
            std::shared_ptr<mad::core::ImmediateDispatcher>(level_dispatcher));
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
    StateMachine::StateId attack_left = machine->add_state(std::make_shared<Attack>(world, hero_id, Movement::Direction::Left,  attack_stage, horizontal_velocity));
    StateMachine::StateId attack_idle= machine->add_state(std::make_shared<Attack>(world, hero_id, Movement::Direction::Idle, attack_stage, horizontal_velocity));
    StateMachine::StateId attack_right = machine->add_state(std::make_shared<Attack>(world, hero_id, Movement::Direction::Right, attack_stage, horizontal_velocity));

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
    machine->add_transition(ground_left, fall_idle, std::make_shared<mad::core::FallCondition>(world, hero_id, 3));
    machine->add_transition(ground_idle, fall_idle, std::make_shared<mad::core::FallCondition>(world, hero_id, 3));
    machine->add_transition(ground_right, fall_idle, std::make_shared<mad::core::FallCondition>(world, hero_id, 3));

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
    controllers.push_back(machine);


    /// add sensor
    auto m_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(hero_id));
    m_entity->add_sensor({0, 6}, 2.65, 0.05);
}
mad::core::Entity::Id mad::core::Hero::get_hero_id() const {
    return hero_id;
}
