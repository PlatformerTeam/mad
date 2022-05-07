#ifndef MAD_GAMERUNNER_HPP
#define MAD_GAMERUNNER_HPP

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <menu/MainMenu.hpp>
#include <menu/AuthorizationMenu.hpp>
#include <loader/LevelLoader.hpp>
#include <runner/Runner.hpp>

#include <memory>
#include <vector>


namespace mad::core {

    class GameRunner : public Runner {
    public:
        explicit GameRunner(
            std::vector<std::shared_ptr<LevelLoader>> level_loaders,
            std::shared_ptr<EventDispatcher> dispatcher,
            std::unique_ptr<MainMenu> main_menu,
//            std::unique_ptr<AuthorizationMenu> auth_menu,
            std::shared_ptr<SystemListener> system_listener
        );

        void start_game();

        void start_authorization();

        void to_main_menu();

        void run(sf::RenderWindow &window) override;

        void stop() override;

    private:
        enum class State {
            MainMenu,
            AuthorizationMenu,
            Gameplay,
        };

        std::vector<std::shared_ptr<LevelLoader>> m_level_loaders;
        std::shared_ptr<EventDispatcher> m_global_event_dispatcher;
        std::unique_ptr<MainMenu> m_main_menu;
//        std::unique_ptr<AuthorizationMenu> m_auth_menu;
        std::shared_ptr<SystemListener> m_system_listener;
        std::unique_ptr<LevelRunner> m_current_level_runner = nullptr;
        State m_current_state = State::MainMenu;
        bool m_running = true;

        void m_sequential_level_run(sf::RenderWindow &window);
    };

}// namespace mad::core

#endif//MAD_GAMERUNNER_HPP
