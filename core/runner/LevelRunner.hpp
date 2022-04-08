#ifndef MAD_LEVELRUNNER_HPP
#define MAD_LEVELRUNNER_HPP

#include <event/management/producer/SystemListener.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <menu/PauseMenu.hpp>
#include <runner/Runner.hpp>
#include <visual/Camera.hpp>
#include <world/World.hpp>


namespace mad::core {

    class LevelRunner : public Runner {
    public:
        explicit LevelRunner(
            std::shared_ptr<SystemListener> system_listener,
            std::shared_ptr<PauseMenu> pause_menu,
            std::shared_ptr<Camera> camera,
            std::shared_ptr<EventDispatcher> global_event_dispatcher,
            std::shared_ptr<EventDispatcher> level_event_dispatcher,
            std::shared_ptr<World> world
        );

        void run(sf::RenderWindow &window) override;

        void stop() override;

        void pause();

        void resume();

    private:
        std::shared_ptr<SystemListener> m_system_listener;
        std::shared_ptr<PauseMenu> m_pause_menu;
        std::shared_ptr<Camera> m_camera;
        std::shared_ptr<EventDispatcher> m_global_event_dispatcher;
        std::shared_ptr<EventDispatcher> m_level_event_dispatcher;
        std::shared_ptr<World> m_world;
        bool m_level_is_running;
        bool m_is_in_pause;
    };

}

#endif//MAD_LEVELRUNNER_HPP
