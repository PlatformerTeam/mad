#ifndef MAD_GAMERUNNER_HPP
#define MAD_GAMERUNNER_HPP

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <menu/Menu.hpp>
#include <loader/LevelLoader.hpp>
#include <runner/Runner.hpp>

#include <memory>
#include <vector>


namespace mad::core {

    class GameRunner : public Runner {
    public:
        explicit GameRunner(std::vector<std::shared_ptr<LevelLoader>> level_loaders, std::shared_ptr<EventDispatcher> dispatcher, std::unique_ptr<Menu> main_menu, std::shared_ptr<SystemListener> system_listener);

        void run(sf::RenderWindow &window) override;

        void stop() override;

    private:
        std::vector<std::shared_ptr<LevelLoader>> m_level_loaders;
        std::shared_ptr<EventDispatcher> m_global_event_dispatcher;
        std::unique_ptr<Menu> m_main_menu;
        std::shared_ptr<SystemListener> m_system_listener;
        bool m_in_main_menu;
    };

}// namespace mad::core

#endif//MAD_GAMERUNNER_HPP
