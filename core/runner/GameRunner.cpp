#include "GameRunner.hpp"

namespace mad::core {

    GameRunner::GameRunner(std::vector<LevelLoader> level_loaders, std::shared_ptr<EventDispatcher> dispatcher,
                           std::unique_ptr<Menu> main_menu) : m_level_loaders(std::move(level_loaders)), m_global_event_dispatcher(std::move(dispatcher)), m_main_menu(std::move(main_menu)) {}

    void GameRunner::run(sf::RenderWindow &window) {

    }

    void GameRunner::stop() {

    }

} // namespace mad::core
