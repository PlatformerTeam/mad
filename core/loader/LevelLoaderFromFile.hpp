#ifndef MAD_LEVELLOADERFROMFILE_HPP
#define MAD_LEVELLOADERFROMFILE_HPP

#include <event/management/controller/Controller.hpp>
#include <event/management/controller/CameraController.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <event/management/handler/LevelRunnerEventsHandler.hpp>
#include <event/management/handler/PauseMenuEventsHandler.hpp>
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

    class ArrowController : public mad::core::EventHandler {
    public:
        explicit ArrowController(std::shared_ptr<mad::core::World> world,
                                 mad::core::Entity::Id entity_id)
                : m_world(std::move(world)),
                  m_entity_id(entity_id) {}

        void handle(const mad::core::Event &event) override {
            //SPDLOG_INFO("handle arrow event");

            auto make_move_intent = [](mad::core::Vec2d dir) {
                return mad::core::LambdaIntent(
                        [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                            mad::core::cast_to<mad::core::ViewableEntity>(entity).move(dir);
                        });
            };

            auto impulse = [](mad::core::Vec2d dir) {
                return mad::core::LambdaIntent(
                        [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                            mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_linear_impulse_to_center(dir, event_dispatcher);
                        });
            };

            auto force = [](mad::core::Vec2d dir) {
                return mad::core::LambdaIntent(
                        [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
                            mad::core::cast_to<mad::core::PhysicalEntity>(entity).apply_force_to_center(dir, event_dispatcher);
                        });
            };

            if (event.type == mad::core::Event::Type::KeyPressed) {
                const auto &keystroke = mad::core::const_cast_to<mad::core::KeyPressed>(event);
                if (keystroke.key_id == sf::Keyboard::Key::Space) {
                    m_world->manipulate_entity_id(m_entity_id, impulse(mad::core::Vec2d{0.0f, -200000.0f}));
                }
            } else if (event.type == mad::core::Event::Type::KeyHeld) {
                const auto &keystroke = mad::core::const_cast_to<mad::core::KeyHeld>(event);
                if (keystroke.key_id == sf::Keyboard::Key::Right) {
                    m_world->manipulate_entity_id(m_entity_id, force(mad::core::Vec2d{100000.0f, 0.0f}));
                }
                if (keystroke.key_id == sf::Keyboard::Key::Left) {
                    m_world->manipulate_entity_id(m_entity_id, force(mad::core::Vec2d{-100000.0f, 0.0f}));
                }
            }
        }

        std::unordered_set<mad::core::Event::Type> handled_types() override {
            return {mad::core::Event::Type::KeyPressed, mad::core::Event::Type::KeyHeld};
        }

    private:
        std::shared_ptr<mad::core::World> m_world;
        mad::core::Entity::Id m_entity_id;
    };


    class LevelLoaderFromFile : public LevelLoader {
    private:
        enum class IdKeys {
            Hero,
            FinishBlock,
        };

    public:
        explicit LevelLoaderFromFile(const std::filesystem::path& path);

        std::unique_ptr<LevelRunner> load(
                std::shared_ptr<EventDispatcher> global_dispatcher,
                std::shared_ptr<SystemListener> system_listener) override;

        std::unordered_map<IdKeys, Entity::Id> create_world(std::shared_ptr<LocalWorld> world);

        void create_block(std::shared_ptr<LocalWorld> world, Vec2d position,
                          float block_size, bool is_stable);

        Entity::Id create_hero(std::shared_ptr<LocalWorld> world, Vec2d position);

        Entity::Id create_finish_block(std::shared_ptr<LocalWorld> world, Vec2d position, float block_size);

    private:
        enum class Objects {
            UnstableBlock,
            StableBlock,
            FinishBlock,
            Hero,
            Enemy1,
            Enemy2,
            Empty,
        };

        std::filesystem::path m_level_directory;

        json m_config_json;

        std::ifstream m_level_map;

        std::unordered_map<char, Objects> m_objects = {
                {'.', Objects::Empty},
                {'#', Objects::StableBlock},
                {'@', Objects::UnstableBlock},
                {'F', Objects::FinishBlock},
                {'H', Objects::Hero},
                {'Z', Objects::Enemy1},
                {'E', Objects::Enemy2}
        };
    };
}

#endif //MAD_LEVELLOADERFROMFILE_HPP
