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

    image_storage = std::make_shared<ImageStorage>(
            std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                    {{ImageStorage::TypeAction::Idle,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["idle"]["source"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["delta_time"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["size_width"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["size_height"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["width_scale"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["height_scale"])
                     },
                     {ImageStorage::TypeAction::Run,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["run"]["source"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["delta_time"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["size_width"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["size_height"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["width_scale"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["height_scale"])
                     },
                     {ImageStorage::TypeAction::Jump,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["jump"]["source"],
                              m_config_json["hero"]["animated"]["actions"]["jump"]["delta_time"],
                              m_config_json["hero"]["animated"]["actions"]["jump"]["size_width"],
                              m_config_json["hero"]["animated"]["actions"]["jump"]["size_height"],
                              m_config_json["hero"]["animated"]["actions"]["jump"]["width_scale"],
                              m_config_json["hero"]["animated"]["actions"]["jump"]["height_scale"])
                     },
                     {ImageStorage::TypeAction::Fly_up,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["fly_up"]["source"],
                              m_config_json["hero"]["animated"]["actions"]["fly_up"]["delta_time"],
                              m_config_json["hero"]["animated"]["actions"]["fly_up"]["size_width"],
                              m_config_json["hero"]["animated"]["actions"]["fly_up"]["size_height"],
                              m_config_json["hero"]["animated"]["actions"]["fly_up"]["width_scale"],
                              m_config_json["hero"]["animated"]["actions"]["fly_up"]["height_scale"])
                     },
                     {ImageStorage::TypeAction::Fall,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["fall"]["source"],
                              m_config_json["hero"]["animated"]["actions"]["fall"]["delta_time"],
                              m_config_json["hero"]["animated"]["actions"]["fall"]["size_width"],
                              m_config_json["hero"]["animated"]["actions"]["fall"]["size_height"],
                              m_config_json["hero"]["animated"]["actions"]["fall"]["width_scale"],
                              m_config_json["hero"]["animated"]["actions"]["fall"]["height_scale"])
                     }}
                    )
    );

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
    machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Idle));
    machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    machine->add_state(std::make_shared<GroundMovement>(world, hero_id, Movement::Direction::Left, horizontal_velocity));
    machine->add_state(std::make_shared<JumpImpulse>(world, hero_id, m_impulse));
    machine->add_state(std::make_shared<StartJump>(world, hero_id, Movement::Direction::Left, horizontal_velocity));
    machine->add_state(std::make_shared<StartJump>(world, hero_id, Movement::Direction::Idle, horizontal_velocity));
    machine->add_state(std::make_shared<StartJump>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    machine->add_state(std::make_shared<FlyUp>(world, hero_id, Movement::Direction::Left, horizontal_velocity)); /// 7
    machine->add_state(std::make_shared<FlyUp>(world, hero_id, Movement::Direction::Idle, horizontal_velocity));
    machine->add_state(std::make_shared<FlyUp>(world, hero_id, Movement::Direction::Right, horizontal_velocity));
    machine->add_state(std::make_shared<Fall>(world, hero_id, Movement::Direction::Left, horizontal_velocity)); /// 10
    machine->add_state(std::make_shared<Fall>(world, hero_id, Movement::Direction::Idle, horizontal_velocity));
    machine->add_state(std::make_shared<Fall>(world, hero_id, Movement::Direction::Right, horizontal_velocity));


    machine->add_transition(0, 1, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(0, 2, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(1, 0, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));
    machine->add_transition(2, 0, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(1, 2, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(2, 1, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(0, 3, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));
    machine->add_transition(1, 3, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));
    machine->add_transition(2, 3, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));

    machine->add_transition(3, 5, std::make_shared<TrueCondition>());
    machine->add_transition(5, 4, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(5, 6, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(4, 5, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(6, 5, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));

    float t1 = 0.1;
    float t2 = 0.2;

    machine->add_transition(4, 8, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Jump));
    machine->add_transition(5, 8, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Jump));
    machine->add_transition(6, 8, std::make_shared<mad::core::EndAnimationCondition>(hero_id, ImageStorage::TypeAction::Jump));

    machine->add_transition(8, 7, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(8, 9, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(7, 8, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(9, 8, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));

    machine->add_transition(7, 11, std::make_shared<mad::core::FallCondition>(world, hero_id));
    machine->add_transition(8, 11, std::make_shared<mad::core::FallCondition>(world, hero_id));
    machine->add_transition(9, 11, std::make_shared<mad::core::FallCondition>(world, hero_id));

    machine->add_transition(11, 10, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(11, 12, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(10, 11, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(12, 11, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));

    machine->add_transition(10, 0, std::make_shared<mad::core::SensorCondition>(hero_id));
    machine->add_transition(11, 0, std::make_shared<mad::core::SensorCondition>(hero_id));
    machine->add_transition(12, 0, std::make_shared<mad::core::SensorCondition>(hero_id));





    machine->set_initial_state(0);
    controllers.push_back(machine);


    /// add sensor
    auto m_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(hero_id));
    m_entity->add_sensor({0, 4}, 0.3, 0.05);
}
mad::core::Entity::Id mad::core::Hero::get_hero_id() const {
    return hero_id;
}
