#include "GameRunner.hpp"

#include <event/system/WindowClose.hpp>

#include <spdlog/spdlog.h>


namespace mad::core {

    GameRunner::GameRunner(
            std::vector<std::shared_ptr<LevelLoader>> level_loaders,
            std::shared_ptr<EventDispatcher> dispatcher,
            std::unique_ptr<MainMenu> main_menu,
            std::unique_ptr<AuthorizationMenu> auth_menu,
            std::shared_ptr<SystemListener> system_listener,
            std::shared_ptr<ClientStorageDriver> client_storage_driver
    ) : m_level_loaders(std::move(level_loaders)),
        m_global_event_dispatcher(std::move(dispatcher)),
        m_main_menu(std::move(main_menu)),
        m_auth_menu(std::move(auth_menu)),
        m_system_listener(std::move(system_listener)),
        m_client_storage_driver(std::move(client_storage_driver)) {
    }

    void GameRunner::run(sf::RenderWindow &window) {
        SPDLOG_DEBUG("Game has started");
        while (m_running) {
            switch (m_current_state) {
                case State::MainMenu: {
                    window.clear(sf::Color(0, 0, 0));
                    m_system_listener->produce(*m_global_event_dispatcher);
                    m_main_menu->render(window);
                    m_main_menu->produce(*m_global_event_dispatcher);
                    window.display();
                } break;
                case State::AuthorizationMenu: {
                    window.clear(sf::Color(0, 0, 0));
                    m_system_listener->produce(*m_global_event_dispatcher);
                    m_auth_menu->render(window);
                    m_auth_menu->produce(*m_global_event_dispatcher);
                    window.display();
                } break;
                case State::Gameplay: {
                    m_sequential_level_run(window);
                } break;
            }
        }
    }

    void GameRunner::stop() {
        m_running = false;
        if (m_current_level_runner) {
            m_current_level_runner->stop();
        }
        m_global_event_dispatcher->dispatch(std::make_shared<WindowClose>());
    }

    void GameRunner::start_game() {
        m_current_state = State::Gameplay;
    }

    void GameRunner::start_authorization() {
        m_current_state = State::AuthorizationMenu;
    }

    void GameRunner::to_main_menu() {
        m_current_state = State::MainMenu;
    }

    void GameRunner::m_sequential_level_run(sf::RenderWindow &window) {
        for (auto &loader: m_level_loaders) {
            if (m_current_state != State::Gameplay) {
                return;
            }
            do {
                m_current_level_runner = loader->load(m_global_event_dispatcher, m_system_listener);
                m_current_level_runner->run(window);
            } while (m_current_state == State::Gameplay && m_current_level_runner->get_state() == LevelRunner::State::Active);
        }
    }

} // namespace mad::core
