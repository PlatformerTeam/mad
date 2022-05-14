#ifndef MAD_HERO_HPP
#define MAD_HERO_HPP

#include "loader/LevelLoaderFromFile.hpp"
#include "world/LocalWorld.hpp"
#include <world/World.hpp>
#include "world/entity/PhysicalEntity.hpp"
#include <filesystem>
namespace mad::core {
    class Hero {
    public:
        Hero(std::shared_ptr<LocalWorld> world, Vec2d position, json m_config_json, std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher, std::vector<std::shared_ptr<mad::core::Controller>> &controllers);
        Entity::Id get_hero_id() const;

    private:
        std::shared_ptr<mad::core::World> m_world;
        Entity::Id hero_id;
        std::shared_ptr<mad::core::ImmediateDispatcher> level_dispatcher;
        int last_pressed_key;
    };
}// namespace mad::core

#endif//MAD_HERO_HPP
