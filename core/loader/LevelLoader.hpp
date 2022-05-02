#ifndef MAD_LEVELLOADER_HPP
#define MAD_LEVELLOADER_HPP

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/producer/SystemListener.hpp>
#include "event/management/handler/LevelRunnerEventsHandler.hpp"
#include "event/management/handler/PauseMenuEventsHandler.hpp"
#include <runner/LevelRunner.hpp>
#include <world/World.hpp>
#include <world/LocalWorld.hpp>

#include <nlohmann/json.hpp>

#include <memory>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>

using nlohmann::json;

namespace mad::core {

    class LevelLoader {
    public:
        explicit LevelLoader(const std::filesystem::path& path);

        std::unique_ptr<LevelRunner> load(
                std::shared_ptr<EventDispatcher> global_dispatcher,
                std::shared_ptr<SystemListener> system_listener);

        Entity::Id create_world(std::shared_ptr<LocalWorld> world);

        void create_block(std::shared_ptr<LocalWorld> world, Vec2d position,
                                        float block_size, bool is_stable);

    private:
        enum class Objects {
            unstable_block,
            stable_block,
            hero,
            enemy_1,
            enemy_2,
            empty
        };

        std::filesystem::path m_level_directory;

        json m_config_json;

        std::ifstream m_level_map;

        std::unordered_map<char, Objects> m_objects = {
                {'.', Objects::empty},
                {'#', Objects::stable_block},
                {'@', Objects::unstable_block},
                {'H', Objects::hero},
                {'Z', Objects::enemy_1},
                {'F', Objects::enemy_2}
        };
    };
}

#endif //MAD_LEVELLOADER_HPP
