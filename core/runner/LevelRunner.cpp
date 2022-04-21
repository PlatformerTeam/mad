#include "LevelRunner.hpp"

#include <spdlog/spdlog.h>


namespace mad::core {

    LevelRunner::LevelRunner(
            std::shared_ptr<SystemListener> system_listener,
            std::shared_ptr<PauseMenu> pause_menu,
            std::shared_ptr<Camera> camera,
            std::shared_ptr<EventDispatcher> global_event_dispatcher,
            std::shared_ptr<EventDispatcher> level_event_dispatcher,
            std::shared_ptr<World> world
    ) : m_system_listener(std::move(system_listener)),
        m_pause_menu(std::move(pause_menu)),
        m_camera(std::move(camera)),
        m_global_event_dispatcher(std::move(global_event_dispatcher)),
        m_level_event_dispatcher(std::move(level_event_dispatcher)),
        m_world(std::move(world)),
        m_level_is_running(true),
        m_is_in_pause(false) {
    }

    void LevelRunner::run(sf::RenderWindow &window) {
        SPDLOG_INFO("Level has started");
        m_camera->turn_on(*m_level_event_dispatcher);
        while (m_level_is_running) {
            window.clear(sf::Color(0, 0, 0));
            if (m_is_in_pause) {
                m_pause_menu->produce(*m_level_event_dispatcher);
                m_system_listener->produce(*m_global_event_dispatcher);
                m_system_listener->produce(*m_level_event_dispatcher);
                m_pause_menu->render(window);
            } else {
                m_world->produce(*m_level_event_dispatcher);
                m_system_listener->produce(*m_global_event_dispatcher);
                m_system_listener->produce(*m_level_event_dispatcher);
                m_camera->render(window);
            }
            window.display();
        }
    }

    void LevelRunner::stop() {
        m_level_is_running = false;
    }

    void LevelRunner::pause() {
        m_is_in_pause = true;
    }

    void LevelRunner::resume() {
        m_is_in_pause = false;
    }

}
