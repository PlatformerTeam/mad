#include "LevelLoader.hpp"

#include <common/Error.hpp>

namespace mad::core {

    LevelLoader::LevelLoader(const std::filesystem::path& path) : m_level_directory(path),
    m_level_map(path / "map") {
        std::ifstream input_config(path / "config.json");
        CHECK_THROW(input_config, FileDoesNotExist, "Config file does not exist");
        CHECK_THROW(m_level_map, FileDoesNotExist, "Map file does not exist");
        input_config >> m_config_json;
    }

    std::unique_ptr<LevelRunner> LevelLoader::load(std::shared_ptr<EventDispatcher> global_dispatcher,
                                                   std::shared_ptr<SystemListener> system_listener) {
        auto level_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

        auto world = std::make_shared<mad::core::LocalWorld>(*level_dispatcher);

        Vec2d camera_position = {m_config_json["camera"]["position"]["x"],
                                 m_config_json["camera"]["position"]["y"]};
        auto camera = std::make_shared<mad::core::Camera>(camera_position, world);

        Entity::Id hero_id = create_world(world);

        camera->turn_on(*level_dispatcher);
        level_dispatcher->registry(camera);
        //level_dispatcher->registry(std::make_shared<ArrowController>(world, hero_id));

        auto level_runner = std::make_unique<mad::core::LevelRunner>(
                system_listener,
                std::make_unique<mad::core::PauseMenu>(),
                camera,
                global_dispatcher,
                level_dispatcher,
                world
        );

        level_dispatcher->registry(std::make_shared<mad::core::LevelRunnerEventsHandler>(*level_runner));
        level_dispatcher->registry(std::make_shared<mad::core::PauseMenuEventsHandler>(*level_runner));

        return level_runner;
    }

    Entity::Id LevelLoader::create_world(std::shared_ptr<LocalWorld> world) {
        float object_size = m_config_json["block"];
        float current_position_x = object_size / 2;
        float current_position_y = object_size / 2;
        Entity::Id hero_id = 0;
        std::string map_line;
        while (std::getline(m_level_map, map_line)) {
            std::cout << map_line <<std::endl;
            for (char object : map_line) {
                switch(m_objects[object]) {
                    case Objects::unstable_block: {
                        create_block(world,
                                     {current_position_x,
                                     current_position_y},
                                     object_size, false);
                        break;
                    }
                    case Objects::stable_block: {
                        create_block(world,
                                              {current_position_x,
                                               current_position_y},
                                              object_size, true);
                        break;
                    }
                    case Objects::hero: {
                        break;
                    }
                    case Objects::enemy_1: {
                        break;
                    }
                    case Objects::enemy_2: {
                        break;
                    }
                    case Objects::empty: {
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

    void LevelLoader::create_block(std::shared_ptr<LocalWorld> world,
                                   Vec2d position, float block_size, bool is_stable) {

        Entity::Id square_id = world->create_physical_entity(
                0,
                position,
                0,
//                std::make_shared<StaticImage>(StaticImage("../../game/resources/static" + (std::string)m_config_json["texture"]["stable"], block_size,
//                                                         block_size, StaticImage::TransformType::Tile)),
                std::make_shared<mad::core::Square>(block_size, mad::core::Color::Green()),
                is_stable
        );
    }

}