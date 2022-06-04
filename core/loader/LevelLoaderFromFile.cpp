#include "LevelLoaderFromFile.hpp"
#include "event/management/condition/KeyDownCondition.hpp"
#include "event/management/condition/KeyPressedCondition.hpp"
#include "event/management/condition/TimerCondition.hpp"
#include "event/management/condition/TrueCondition.hpp"
#include "event/management/controller/statemachine/EnemyStateMachine.hpp"
#include "event/management/controller/statemachine/HeroStateMachine.hpp"
#include "event/management/controller/statemachine/StateMachine.hpp"
#include <../../game/mobs/hero/Hero.hpp>
#include <event/management/condition/CollisionCondition.hpp>

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
        level_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

        auto world = std::make_shared<mad::core::LocalWorld>(*level_dispatcher);

        Vec2d camera_position = {m_config_json["camera"]["position"]["x"],
                                 m_config_json["camera"]["position"]["y"]};
        float camera_smoothness = m_config_json["camera"]["smoothness"];
        Camera::FollowType camera_type = m_config_json["camera"]["follow_type"] == "forward" ?
                                         Camera::FollowType::Forward : Camera::FollowType::Backward;
        float minimal_distance = m_config_json["camera"]["minimal_distance"];
        float zoom = m_config_json["camera"]["zoom"];
        float part_of_window = m_config_json["camera"]["part_of_window"];

        auto camera = std::make_shared<mad::core::Camera>(camera_position, world, true);

        controllers = {std::make_shared<mad::core::CameraController>(
                camera)};


        //Entity::Id hero_id = create_world(world);
        auto keys = create_world(world);

        camera->turn_on(*level_dispatcher, keys[LevelLoaderFromFile::IdKeys::Hero], camera_smoothness,
                        camera_type, minimal_distance, part_of_window);
        level_dispatcher->registry(camera);
        //level_dispatcher->registry(std::make_shared<ArrowController>(world, keys[LevelLoaderFromFile::IdKeys::Hero]));

        /* std::vector<std::shared_ptr<mad::core::Controller>> controllers {
                 std::make_shared<mad::core::CameraController>(camera)
         };*/

        /*///State Machine
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
                                                                                camera)};*/

        camera->set_zoom(zoom);


        auto level_runner = std::make_unique<mad::core::LevelRunner>(
                system_listener,
                std::make_unique<mad::core::PauseMenu>(),
                camera,
                global_dispatcher,
                level_dispatcher,
                world,
                controllers);

        level_dispatcher->registry(std::make_shared<mad::core::LevelRunnerEventsHandler>(*level_runner, std::make_shared<CollisionCondition>(keys[LevelLoaderFromFile::IdKeys::Hero], keys[LevelLoaderFromFile::IdKeys::FinishBlock])));
        level_dispatcher->registry(std::make_shared<mad::core::PauseMenuEventsHandler>(*level_runner));

        return level_runner;
    }

    std::unordered_map<LevelLoaderFromFile::IdKeys, Entity::Id> LevelLoaderFromFile::create_world(std::shared_ptr<LocalWorld> world) {
        m_level_map = std::ifstream(m_level_directory / "map");
        float object_size = m_config_json["block"];
        float current_position_x = object_size / 2;
        float current_position_y = object_size / 2;
        std::unordered_map<LevelLoaderFromFile::IdKeys, Entity::Id> keys;
        Entity::Id hero_id = 0;
        std::string map_line;

        create_background(world);

        while (std::getline(m_level_map, map_line)) {
            for (char object : map_line) {
                switch (m_objects[object]) {
                    case Objects::UnstableBlock: {
                        create_block(world,
                                     {current_position_x,
                                      current_position_y},
                                     object_size, false, m_objects[object]);
                        break;
                    }
                    case Objects::GroundBlock: {
                        create_block(world,
                                     {current_position_x,
                                      current_position_y},
                                     object_size, true, m_objects[object]);
                        break;
                    }
                    case Objects::BeginBlock: {
                        create_block(world,
                                     {current_position_x,
                                      current_position_y},
                                     object_size, true, m_objects[object]);
                        break;
                    }
                    case Objects::MiddleBlock: {
                        create_block(world,
                                     {current_position_x,
                                      current_position_y},
                                     object_size, true, m_objects[object]);
                        break;
                    }
                    case Objects::EndBlock: {
                        create_block(world,
                                     {current_position_x,
                                      current_position_y},
                                     object_size, true, m_objects[object]);
                        break;
                    }
                    case Objects::SeparateBlock: {
                        create_block(world,
                                     {current_position_x,
                                      current_position_y},
                                     object_size, true, m_objects[object]);
                        break;
                    }
                    case Objects::Decoration1: {
                        create_decoration(world,
                                     {current_position_x,
                                      current_position_y},
                                      m_objects[object]);
                        break;
                    }
                    case Objects::Decoration2: {
                        create_decoration(world,
                                     {current_position_x,
                                      current_position_y},
                                      m_objects[object]);
                        break;
                    }
                    case Objects::FinishBlock: {
                        keys[LevelLoaderFromFile::IdKeys::FinishBlock] = create_finish_block(
                                world,
                                {current_position_x, current_position_y},
                                object_size);
                        break;
                    }
                    case Objects::Hero: {
                        // Hero hero(world, {current_position_x, current_position_y}, m_config_json, level_dispatcher, controllers);
                        hero_id = create_hero(world, {current_position_x, current_position_y});
                        keys[LevelLoaderFromFile::IdKeys::Hero] = hero_id;
                        break;
                    }
                    case Objects::Enemy1: {
                        break;
                    }
                    case Objects::Enemy2: {
                        create_mob(world, {current_position_x, current_position_y});
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

    void LevelLoaderFromFile::create_block(std::shared_ptr<LocalWorld> world, Vec2d position,
                                           float block_size, bool is_stable, Objects object) {

        std::filesystem::path source(m_config_json["static_resources"]);

        switch (object) {
            case Objects::UnstableBlock: {
                source /= m_config_json["texture"]["unstable_block"];
                break;
            }
            case Objects::GroundBlock: {
                source /= m_config_json["texture"]["ground_block"];
                break;
            }
            case Objects::BeginBlock: {
                source /= m_config_json["texture"]["begin_block"];
                break;
            }
            case Objects::MiddleBlock: {
                source /= m_config_json["texture"]["middle_block"];
                break;
            }
            case Objects::EndBlock: {
                source /= m_config_json["texture"]["end_block"];
                break;
            }
            case Objects::SeparateBlock: {
                source /= m_config_json["texture"]["separate_block"];
                break;
            }
        }

        auto image_storage = std::make_shared<ImageStorage>(
                std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                        {{ImageStorage::TypeAction::Idle,
                          std::make_shared<StaticImage>(source, block_size,
                                                        block_size,
                                                        StaticImage::TransformType::Fit)
                         }}));

        Entity::Id square_id = world->create_physical_entity(
                1,
                position,
                0,
                image_storage,
                is_stable);
    }

    void LevelLoaderFromFile::create_decoration(std::shared_ptr<LocalWorld> world, Vec2d position, Objects object) {
        std::filesystem::path source(m_config_json["decoration_resources"]);

        float decoration_scale = 1;
        float delta_x = 0;
        float delta_y = 0;

        switch (object) {
            case Objects::Decoration1 : {
                source /= m_config_json["decoration"]["decoration_01"]["source"];
                decoration_scale = m_config_json["decoration"]["decoration_01"]["scale"];
                delta_x = m_config_json["decoration"]["decoration_01"]["delta_x"];
                delta_y = m_config_json["decoration"]["decoration_01"]["delta_y"];
                break;
            }
            case Objects::Decoration2 : {
                source /= m_config_json["decoration"]["decoration_02"]["source"];
                decoration_scale = m_config_json["decoration"]["decoration_02"]["scale"];
                delta_x = m_config_json["decoration"]["decoration_02"]["delta_x"];
                delta_y = m_config_json["decoration"]["decoration_02"]["delta_y"];
                break;
            }
        }
        decoration_scale *= static_cast<float>(m_config_json["camera"]["zoom"]);

        auto image_storage = std::make_shared<ImageStorage>(
                std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                        {{ImageStorage::TypeAction::Idle,
                          std::make_shared<DecorationImage>(source, decoration_scale, delta_x, delta_y)
                         }}));

        Entity::Id decoration_id = world->create_viewable_entity(
                0,
                position,
                0,
                image_storage
        );
    }

    Entity::Id LevelLoaderFromFile::create_hero(std::shared_ptr<LocalWorld> world, Vec2d position) {
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
                        {{ImageStorage::TypeAction::Jump,
                          std::make_shared<AnimatedImageSeveralFiles>(
                                  source / m_config_json["hero"]["animated"]["actions"]["jump"]["source"],

                                  m_config_json["hero"]["animated"]["actions"]["jump"]["delta_time"],
                                  physical_size_width, physical_size_height, size_scale,
                                  delta_x, delta_y)},
                         {ImageStorage::TypeAction::Idle,
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
                                  delta_x, delta_y)}}));

        hero_id = world->create_physical_entity(
                2,
                position,
                0,
                image_storage,
                false, false,
                0x0004, 0x0002);

        /// add sensor
        auto m_entity = cast_to_or_null<PhysicalEntity>(world->get_storage().get_entity(hero_id));
        m_entity->add_sensor({0, 6}, 2.65, 0.05);

        float m_impulse = 2000;
        float horizontal_velocity = 20;

        auto machine = std::make_shared<mad::core::HeroStateMachine>(world, position, hero_id, level_dispatcher, m_impulse, horizontal_velocity);
        controllers.push_back(machine);

        return hero_id;
    }


    void LevelLoaderFromFile::create_mob(std::shared_ptr<LocalWorld> world, Vec2d position) {
        std::filesystem::path source(m_config_json["animated_resources"]);
        source /= m_config_json["enemy"]["source"];

        std::shared_ptr<ImageStorage> image_storage;

        float physical_size_width = m_config_json["enemy"]["animated"]["size_width"];
        float physical_size_height = m_config_json["enemy"]["animated"]["size_height"];
        float size_scale = m_config_json["enemy"]["animated"]["size_scale"];
        float delta_x = m_config_json["enemy"]["animated"]["delta_x"];
        float delta_y = m_config_json["enemy"]["animated"]["delta_y"];


        image_storage = std::make_shared<ImageStorage>(
                std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                        {{ImageStorage::TypeAction::Idle,
                          std::make_shared<AnimatedImageSeveralFiles>(
                                  source / m_config_json["enemy"]["animated"]["actions"]["idle"]["source"],

                                  m_config_json["enemy"]["animated"]["actions"]["idle"]["delta_time"],
                                  physical_size_width, physical_size_height, size_scale,
                                  delta_x, delta_y)},
                         {ImageStorage::TypeAction::Run,
                          std::make_shared<AnimatedImageSeveralFiles>(
                                  source / m_config_json["enemy"]["animated"]["actions"]["run"]["source"],

                                  m_config_json["enemy"]["animated"]["actions"]["run"]["delta_time"],
                                  physical_size_width, physical_size_height, size_scale,
                                  delta_x, delta_y)},
                         {ImageStorage::TypeAction::Attack_1_beg,
                          std::make_shared<AnimatedImageSeveralFiles>(
                                  source / m_config_json["enemy"]["animated"]["actions"]["attack_beg"]["source"],

                                  m_config_json["enemy"]["animated"]["actions"]["attack_beg"]["delta_time"],
                                  physical_size_width, physical_size_height, size_scale,
                                  delta_x, delta_y)},
                         {ImageStorage::TypeAction::Attack_1_end,
                          std::make_shared<AnimatedImageSeveralFiles>(
                                  source / m_config_json["enemy"]["animated"]["actions"]["attack_end"]["source"],

                                  m_config_json["enemy"]["animated"]["actions"]["attack_end"]["delta_time"],
                                  physical_size_width, physical_size_height, size_scale,
                                  delta_x, delta_y)}}));

        Entity::Id enemy_id = world->create_physical_entity(
                2,
                position,
                0,
                image_storage,
                false, false,
                0x0004, 0x0002);


        float m_impulse = 2000;
        float horizontal_velocity = 5.5f;

        auto machine = std::make_shared<mad::core::EnemyStateMachine>(world, position, enemy_id, level_dispatcher, m_impulse, horizontal_velocity);
        controllers.push_back(machine);
    }
    Entity::Id LevelLoaderFromFile::create_finish_block(std::shared_ptr<LocalWorld> world, Vec2d position, float block_size) {
        std::filesystem::path source(m_config_json["static_resources"]);
        source /= static_cast<std::string>(m_config_json["texture"]["finish_block"]);

        auto image_storage = std::make_shared<ImageStorage>(
                std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                        {{ImageStorage::TypeAction::Idle,
                          std::make_shared<StaticImage>(source, block_size,
                                                        block_size,
                                                        StaticImage::TransformType::Fit)}}));

        return world->create_physical_entity(
                1,
                position,
                0,
                image_storage,
                true);
    }

    void LevelLoaderFromFile::create_background(std::shared_ptr<LocalWorld> world) {
        std::filesystem::path source(m_config_json["background"]["source"]);

        std::shared_ptr<ImageStorage> image_storage;
        std::vector<float> parallax_ratios = m_config_json["background"]["parallax_ratios"];

        image_storage = std::make_shared<ImageStorage>(
                std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>>(
                        {{ImageStorage::TypeAction::Idle,
                          std::make_shared<BackgroundImage>(
                                  source,
                                  parallax_ratios)
                                  }}));
        world->create_viewable_entity(
                -1,
                {0, 0},
                0,
                image_storage);
    }


}// namespace mad::core
