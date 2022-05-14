#include "Hero.hpp"
#include "event/management/condition/KeyDownCondition.hpp"
#include "event/management/condition/KeyPressedCondition.hpp"
#include "event/management/condition/KeyReleasedCondition.hpp"
#include "event/management/condition/LastStateCondition.hpp"
#include "event/management/condition/TimerCondition.hpp"
#include "event/management/condition/TrueCondition.hpp"
#include "event/management/controller/Idle.hpp"
#include "event/management/controller/Jump.hpp"
#include "event/management/controller/Run.hpp"
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
                              m_config_json["hero"]["animated"]["actions"]["idle"]["count_files"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["delta_time"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["size_width"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["size_height"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["width_scale"],
                              m_config_json["hero"]["animated"]["actions"]["idle"]["height_scale"])
                     },
                     {ImageStorage::TypeAction::Run,
                      std::make_shared<AnimatedImageSeveralFiles>(
                              source / m_config_json["hero"]["animated"]["actions"]["run"]["source"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["count_files"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["delta_time"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["size_width"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["size_height"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["width_scale"],
                              m_config_json["hero"]["animated"]["actions"]["run"]["height_scale"])
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
    machine->add_state(std::make_shared<Idle>());
    machine->add_state(std::make_shared<Run>(world, hero_id, Run::Direction::Right));
    machine->add_state(std::make_shared<Run>(world, hero_id, Run::Direction::Left));
    machine->add_state(std::make_shared<Jump>(world, hero_id));
    machine->add_transition(0, 1, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(0, 2, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(1, 0, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Right));
    machine->add_transition(2, 0, std::make_shared<mad::core::KeyReleasedCondition>(sf::Keyboard::Left));
    machine->add_transition(1, 2, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Left));
    machine->add_transition(2, 1, std::make_shared<mad::core::KeyDownCondition>(sf::Keyboard::Right));
    machine->add_transition(0, 3, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));
    machine->add_transition(1, 3, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));
    machine->add_transition(2, 3, std::make_shared<mad::core::KeyPressedCondition>(sf::Keyboard::Space));
    machine->add_transition(3, 0, std::make_shared<mad::core::LastStateCondition>(machine, 0));
    machine->add_transition(3, 1, std::make_shared<mad::core::LastStateCondition>(machine, 1));
    machine->add_transition(3, 2, std::make_shared<mad::core::LastStateCondition>(machine, 2));
    machine->set_initial_state(0);
    controllers.push_back(machine);
}
mad::core::Entity::Id mad::core::Hero::get_hero_id() const {
    return hero_id;
}
