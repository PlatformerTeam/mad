#include "LevelLoaderFromServer.hpp"

#include <event/management/condition/CollisionCondition.hpp>
#include "event/management/condition/KeyDownCondition.hpp"
#include "event/management/condition/KeyPressedCondition.hpp"
#include "event/management/condition/TimerCondition.hpp"
#include "event/management/condition/TrueCondition.hpp"
#include "event/management/controller/statemachine/StateMachine.hpp"

#include <common/Error.hpp>

namespace mad::core {

    LevelLoaderFromServer::LevelLoaderFromServer(std::string map, json config) : m_level_map(std::move(map)), m_config_json(std::move(config)) { }

    std::unique_ptr<LevelRunner> LevelLoaderFromServer::load(std::shared_ptr<EventDispatcher> global_dispatcher,
                                                           std::shared_ptr<SystemListener> system_listener) {
        auto level_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

        auto world = std::make_shared<mad::core::LocalWorld>(*level_dispatcher);

        Vec2d camera_position = {m_config_json["camera"]["position"]["x"],
                                 m_config_json["camera"]["position"]["y"]};
        auto camera = std::make_shared<mad::core::Camera>(camera_position, world);

        auto keys = create_world(world);

        camera->turn_on(*level_dispatcher, keys[LevelLoaderFromServer::IdKeys::Hero]);
        level_dispatcher->registry(camera);
        level_dispatcher->registry(std::make_shared<ArrowController>(world, keys[LevelLoaderFromServer::IdKeys::Hero]));

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

        level_dispatcher->registry(std::make_shared<mad::core::LevelRunnerEventsHandler>(*level_runner, std::make_shared<CollisionCondition>(keys[LevelLoaderFromServer::IdKeys::Hero], keys[LevelLoaderFromServer::IdKeys::FinishBlock])));
        level_dispatcher->registry(std::make_shared<mad::core::PauseMenuEventsHandler>(*level_runner));

        return level_runner;
    }

    std::unordered_map<LevelLoaderFromServer::IdKeys, Entity::Id> LevelLoaderFromServer::create_world(std::shared_ptr<LocalWorld> world) {
        float object_size = m_config_json["block"];
        float current_position_x = object_size / 2;
        float current_position_y = object_size / 2;
        std::size_t width = m_config_json["width"];
        std::unordered_map<LevelLoaderFromServer::IdKeys, Entity::Id> keys;

        create_background(world);

        for (std::size_t i = 0; i < m_level_map.size();) {
            for (std::size_t j = 0; j < width; ++j, ++i) {
                char object = m_level_map[i];
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
                    case Objects::FinishBlock: {
                        keys[LevelLoaderFromServer::IdKeys::FinishBlock] = create_finish_block(
                                world,
                                {current_position_x, current_position_y},
                                object_size);
                        break;
                    }
                    case Objects::Hero: {
                        keys[LevelLoaderFromServer::IdKeys::Hero] = create_hero(world,
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
        return keys;
    }

    void LevelLoaderFromServer::create_block(std::shared_ptr<LocalWorld> world,
                                           Vec2d position, float block_size, bool is_stable) {

        std::filesystem::path source("../../resources/static/");
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

    Entity::Id LevelLoaderFromServer::create_hero(std::shared_ptr<LocalWorld> world, Vec2d position) {
        std::filesystem::path source(m_config_json["animated_resources"]);
        source /= m_config_json["hero"]["source"];

        Entity::Id hero_id = 0;

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
                                  delta_x, delta_y)
                         },
                         {ImageStorage::TypeAction::Run,
                          std::make_shared<AnimatedImageSeveralFiles>(
                                  source / m_config_json["hero"]["animated"]["actions"]["run"]["source"],
                                  m_config_json["hero"]["animated"]["actions"]["run"]["delta_time"],
                                  physical_size_width, physical_size_height, size_scale,
                                  delta_x, delta_y)
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

    Entity::Id LevelLoaderFromServer::create_finish_block(std::shared_ptr<LocalWorld> world, Vec2d position, float block_size) {
        std::filesystem::path source("../../resources/static/");
        source /= static_cast<std::string>(m_config_json["texture"]["finish"]);

        auto image_storage = std::make_shared<ImageStorage>(
                std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                        {{ImageStorage::TypeAction::Idle,
                          std::make_shared<StaticImage>(source, block_size,
                                                        block_size,
                                                        StaticImage::TransformType::Fit)
                        }}));

        return world->create_physical_entity(
                0,
                position,
                0,
                image_storage,
                true
        );
    }

    void LevelLoaderFromServer::create_background(std::shared_ptr<LocalWorld> world) {
        std::filesystem::path source(m_config_json["background"]["source"]);

        std::shared_ptr<ImageStorage> image_storage;
        std::vector<float> parallax_ratios = m_config_json["background"]["parallax_ratios"];

        image_storage = std::make_shared<ImageStorage>(
                std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                        {{ImageStorage::TypeAction::Idle,
                          std::make_shared<BackgroundImage>(
                                  source,
                                  parallax_ratios,
                                  m_config_json["background"]["scale"]
                                  )
                        }}
                        )
        );
        world->create_viewable_entity(
                -1,
                {0, 0},
                0,
                image_storage
        );
    }

}