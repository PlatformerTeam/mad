#ifndef MAD_LEVELLOADERFROMFILE_HPP
#define MAD_LEVELLOADERFROMFILE_HPP

#include <event/management/controller/Controller.hpp>
#include <event/management/controller/CameraController.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <event/management/handler/LevelRunnerEventsHandler.hpp>
#include <event/management/handler/PauseMenuEventsHandler.hpp>
#include <event/management/condition/CollisionCondition.hpp>
#include <event/system/KeyHeld.hpp>
#include <event/system/KeyPressed.hpp>
#include <runner/LevelRunner.hpp>
#include <world/World.hpp>
#include <world/LocalWorld.hpp>

#include <loader/LevelLoader.hpp>

#include  <nlohmann/json.hpp>

#include <memory>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>

using json = nlohmann::json;

namespace mad::core {




    class LevelLoaderFromFile : public LevelLoader {
    private:
        enum class IdKeys {
            Hero,
            FinishBlock,
        };

        enum class Objects;

    public:

        explicit LevelLoaderFromFile(const std::filesystem::path& path);

        std::unique_ptr<LevelRunner> load(
                std::shared_ptr<EventDispatcher> global_dispatcher,
                std::shared_ptr<SystemListener> system_listener) override;

        std::unordered_map<IdKeys, Entity::Id> create_world(std::shared_ptr<LocalWorld> world);

        void create_block(std::shared_ptr<LocalWorld> world, Vec2d position,
                          float block_size, bool is_stable, Objects object);

        Entity::Id create_hero(std::shared_ptr<LocalWorld> world, Vec2d position);

        void create_mob(std::shared_ptr<LocalWorld> world, Vec2d position);

        void create_background(std::shared_ptr<LocalWorld> world);

        Entity::Id create_finish_block(std::shared_ptr<LocalWorld> world, Vec2d position, float block_size);

        void create_decoration(std::shared_ptr<LocalWorld> world, Vec2d position, Objects object);

    private:
        enum class Objects {
            UnstableBlock,
            GroundBlock,
            FinishBlock,
            BeginBlock,
            MiddleBlock,
            EndBlock,
            SeparateBlock,
            Decoration1,
            Decoration2,
            Hero,
            Enemy1,
            Enemy2,
            Empty
        };

        std::filesystem::path m_level_directory;

        json m_config_json;

        std::ifstream m_level_map;

        std::vector<std::shared_ptr<mad::core::Controller>> controllers;

        std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher;

        std::unordered_map<char, Objects> m_objects = {
                {'.', Objects::Empty},
                {'#', Objects::GroundBlock},
                {'@', Objects::UnstableBlock},
                {'F', Objects::FinishBlock},
                {'[', Objects::BeginBlock},
                {'_', Objects::MiddleBlock},
                {']', Objects::EndBlock},
                {'+', Objects::SeparateBlock},
                {'*', Objects::Decoration1},
                {'&', Objects::Decoration2},
                {'H', Objects::Hero},
                {'Z', Objects::Enemy1},
                {'E', Objects::Enemy2}
        };

        int r_hero_id;
    };
}

#endif //MAD_LEVELLOADERFROMFILE_HPP
