#include "LevelLoaderFromFile.hpp"

#include <common/Error.hpp>

namespace mad::core {

    LevelLoaderFromFile::LevelLoaderFromFile(const std::filesystem::path& path) : m_level_directory(path),
    m_level_map(path / "map") {
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

        std::vector<std::shared_ptr<mad::core::Controller>> controllers {
                std::make_shared<mad::core::CameraController>(camera)
        };

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
        float object_size = m_config_json["block"];
        float current_position_x = object_size / 2;
        float current_position_y = object_size / 2;
        Entity::Id hero_id = 0;
        std::string map_line;
        while (std::getline(m_level_map, map_line)) {
            for (char object : map_line) {
                switch(m_objects[object]) {
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

        std::string source = "../../game/resources/static/";
        if (is_stable) {
            source += static_cast<std::string>(m_config_json["texture"]["stable"]);
        } else {
            source += static_cast<std::string>(m_config_json["texture"]["unstable"]);
        }

        Entity::Id square_id = world->create_physical_entity(
                0,
                position,
                0,
                std::make_shared<StaticImage>(source, block_size, block_size, StaticImage::TransformType::Tile),
                is_stable
        );
    }

    Entity::Id LevelLoaderFromFile::create_hero(std::shared_ptr<LocalWorld> world, Vec2d position) {
        std::filesystem::path source(m_config_json["animated_resources"]);
        source /= m_config_json["hero"]["animated"]["resource"];

        Entity::Id hero_id = 0;
        if (static_cast<std::string>(m_config_json["hero"]["animated"]["type"]) == "several_files") {
            hero_id = world->create_physical_entity(
                    0,
                    position,
                    0,
                    std::make_shared<AnimatedImageSeveralFiles>(source,
                                                                m_config_json["hero"]["animated"]["count_files"],
                                                                m_config_json["hero"]["animated"]["delta_time"],
                                                                m_config_json["hero"]["animated"]["size_width"],
                                                                m_config_json["hero"]["animated"]["size_height"],
                                                                m_config_json["hero"]["animated"]["width_scale"],
                                                                m_config_json["hero"]["animated"]["height_scale"]),
                    false, false
            );
        } else {
            hero_id = world->create_physical_entity(
                    0,
                    position,
                    0,
                    std::make_shared<AnimatedImageOneFile>(source,
                                                           m_config_json["hero"]["animated"]["sprite_width"],
                                                           m_config_json["hero"]["animated"]["sprite_height"],
                                                           m_config_json["hero"]["animated"]["delta_time"],
                                                           m_config_json["hero"]["animated"]["size_width"],
                                                           m_config_json["hero"]["animated"]["size_height"],
                                                           m_config_json["hero"]["animated"]["width_scale"],
                                                           m_config_json["hero"]["animated"]["height_scale"]),
                    false, false
            );
        }
        return hero_id;
    }

}