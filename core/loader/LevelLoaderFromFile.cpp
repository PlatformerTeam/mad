#include "LevelLoaderFromFile.hpp"
#include "event/management/condition/KeyDownCondition.hpp"
#include "event/management/condition/KeyPressedCondition.hpp"
#include "event/management/condition/TimerCondition.hpp"
#include "event/management/condition/TrueCondition.hpp"
#include "event/management/controller/statemachine/StateMachine.hpp"

#include <common/Error.hpp>

namespace mad::core {

    LevelLoaderFromFile::LevelLoaderFromFile(const std::filesystem::path &path) : m_level_directory(path) {
        std::ifstream input_config(path / "config.json");
        CHECK_THROW(input_config, FileDoesNotExist, "Config file does not exist");
        CHECK_THROW(m_level_map, FileDoesNotExist, "Map file does not exist");
        input_config >> m_config_json;
    }

    std::unique_ptr<LevelRunner> LevelLoaderFromFile::load(std::shared_ptr<EventDispatcher> global_dispatcher,
                                                           std::shared_ptr<SystemListener> system_listener) {
        auto level_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

        auto world = std::make_shared<mad::core::LocalWorld>(*level_dispatcher);

        Vec2d camera_position = {m_config_json["camera"]["position"]["x"],
                                 m_config_json["camera"]["position"]["y"]};
        auto camera = std::make_shared<mad::core::Camera>(camera_position, world);

        Entity::Id hero_id = create_world(world);

        camera->turn_on(*level_dispatcher, hero_id);
        level_dispatcher->registry(camera);
        level_dispatcher->registry(std::make_shared<ArrowController>(world, hero_id));

        /* std::vector<std::shared_ptr<mad::core::Controller>> controllers {
                 std::make_shared<mad::core::CameraController>(camera)
         };*/

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
        machine->add_state(std::make_shared<C1>());
        machine->add_state(std::make_shared<C2>());
        machine->add_transition(0, 1, std::make_shared<mad::core::TimerCondition>(1));
        machine->add_transition(1, 0, std::make_shared<mad::core::TimerCondition>(2));
        machine->set_initial_state(0);
        std::vector<std::shared_ptr<mad::core::Controller>> controllers{machine,
                                                                        std::make_shared<mad::core::CameraController>(
                                                                                camera)};

        auto level_runner = std::make_unique<mad::core::LevelRunner>(
                system_listener,
                std::make_unique<mad::core::PauseMenu>(),
                camera,
                global_dispatcher,
                level_dispatcher,
                world,
                controllers
        );

        level_dispatcher->registry(std::make_shared<mad::core::LevelRunnerEventsHandler>(*level_runner));
        level_dispatcher->registry(std::make_shared<mad::core::PauseMenuEventsHandler>(*level_runner));

        return level_runner;
    }

    Entity::Id LevelLoaderFromFile::create_world(std::shared_ptr<LocalWorld> world) {
        m_level_map = std::ifstream(m_level_directory / "map");
        float object_size = m_config_json["block"];
        float current_position_x = object_size / 2;
        float current_position_y = object_size / 2;
        Entity::Id hero_id = 0;
        std::string map_line;
        while (std::getline(m_level_map, map_line)) {
            for (char object: map_line) {
                switch (m_objects[object]) {
                    case Objects::UnstableBlock: {
                        create_block(world,
                                     {current_position_x,
                                      current_position_y},
                                     object_size, false);
                        break;
                    }
                    case Objects::StableBlock: {
                        create_block(world,
                                     {current_position_x,
                                      current_position_y},
                                     object_size, true);
                        break;
                    }
                    case Objects::Hero: {
                        hero_id = create_hero(world,
                                              {current_position_x,
                                               current_position_y});
                        break;
                    }
                    case Objects::Enemy1: {
                        break;
                    }
                    case Objects::Enemy2: {
                        break;
                    }
                    case Objects::Empty: {
                        break;
                    }
                }
                current_position_x += object_size;
            }
            current_position_y += object_size;
            current_position_x = object_size / 2;
        }
        return hero_id;
    }

    void LevelLoaderFromFile::create_block(std::shared_ptr<LocalWorld> world,
                                           Vec2d position, float block_size, bool is_stable) {

        std::filesystem::path source("../../game/resources/static/");
        if (is_stable) {
            source /= static_cast<std::string>(m_config_json["texture"]["stable"]);
        } else {
            source /= static_cast<std::string>(m_config_json["texture"]["unstable"]);
        }

        auto image_storage = std::make_shared<ImageStorage>(
                std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                        {{ImageStorage::TypeAction::Idle,
                          std::make_shared<StaticImage>(source, block_size,
                                                        block_size,
                                                        StaticImage::TransformType::Tile)
                         }}));

        Entity::Id square_id = world->create_physical_entity(
                0,
                position,
                0,
                image_storage,
                is_stable
        );
    }

    Entity::Id LevelLoaderFromFile::create_hero(std::shared_ptr<LocalWorld> world, Vec2d position) {
        std::filesystem::path source(m_config_json["animated_resources"]);
        source /= m_config_json["hero"]["source"];

        Entity::Id hero_id = 0;

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

        return hero_id;
    }

}