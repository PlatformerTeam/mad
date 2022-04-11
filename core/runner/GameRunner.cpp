#include "GameRunner.hpp"

namespace mad::core {

    GameRunner::GameRunner(std::vector<std::shared_ptr<LevelLoader>> level_loaders, std::shared_ptr<EventDispatcher> dispatcher,
                           std::unique_ptr<Menu> main_menu, std::shared_ptr<SystemListener> system_listener) : m_level_loaders(std::move(level_loaders)), m_global_event_dispatcher(std::move(dispatcher)), m_main_menu(std::move(main_menu)), m_system_listener(std::move(system_listener)), m_in_main_menu(true) {}

    void GameRunner::run(sf::RenderWindow &window) {
        while (m_in_main_menu) {
            m_system_listener->produce(*m_global_event_dispatcher);
            m_main_menu->render(window);
        }
        for (auto &loader : m_level_loaders) {
            auto level = loader->load();
            level->run(window);
        }
    }

    void GameRunner::stop() {

    }

} // namespace mad::core
