#include "GameRunner.hpp"

namespace mad::core {

    GameRunner::GameRunner(
            std::vector<std::shared_ptr<LevelLoader>> level_loaders,
            std::shared_ptr<EventDispatcher> dispatcher,
            std::unique_ptr<MainMenu> main_menu,
            std::shared_ptr<SystemListener> system_listener
    ) : m_level_loaders(std::move(level_loaders)),
        m_global_event_dispatcher(std::move(dispatcher)),
        m_main_menu(std::move(main_menu)),
        m_system_listener(std::move(system_listener)) {
    }

    void GameRunner::run(sf::RenderWindow &window) {
        //m_in_main_menu = false;
        while (m_running) {
            if (m_in_main_menu) {
                window.clear(sf::Color(0, 0, 0));
                m_system_listener->produce(*m_global_event_dispatcher);
                m_main_menu->render(window);
                m_main_menu->produce(*m_global_event_dispatcher);
                window.display();
            } else {
                for (auto &loader: m_level_loaders) {
                    if (m_in_main_menu) {
                        return;
                    }
                    m_current_level_runner = loader->load(m_global_event_dispatcher, m_system_listener);
                    m_current_level_runner->run(window);
                }
            }
        }
    }

    void GameRunner::stop() {
        m_running = false;
        if (m_current_level_runner) {
            m_current_level_runner->stop();
        }
    }

    void GameRunner::start_game() {
        m_in_main_menu = false;
    }

} // namespace mad::core
