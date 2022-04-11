#ifndef MAD_GAMERUNNER_HPP
#define MAD_GAMERUNNER_HPP

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <menu/Menu.hpp>
#include <runner/LevelLoader.hpp>
#include <runner/Runner.hpp>

#include <memory>
#include <vector>


namespace mad::core {

    class GameRunner : public Runner {
    public:
        explicit GameRunner(std::vector<LevelLoader> level_loaders, std::shared_ptr<EventDispatcher> dispatcher, std::unique_ptr<Menu> main_menu);

        void run(sf::RenderWindow &window) override;

        void stop() override;

    private:
        std::vector<LevelLoader> m_level_loaders;
        std::shared_ptr<EventDispatcher> m_global_event_dispatcher;
        std::unique_ptr<Menu> m_main_menu;
    };

}// namespace mad::core

#endif//MAD_GAMERUNNER_HPP
