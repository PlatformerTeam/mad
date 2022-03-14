#include "SequentialRunner.hpp"

#include <visual/Camera.hpp>

#include <spdlog/spdlog.h>


void mad::core::SequentialRunner::run(sf::RenderWindow &window) {
    m_dispatcher->registry(m_camera);
    m_camera->turn_on(*m_dispatcher);
    while (true) {
        for (const auto &producer : m_producers) {
            producer->produce(*m_dispatcher);
        }
        for (const auto &renderable : m_renderables) {
            renderable->render(window);
        }
        window.display();
    }
}

mad::core::SequentialRunner::SequentialRunner(
        std::vector<std::shared_ptr<EventProducer>> producers,
        std::vector<std::shared_ptr<Renderable>> renderables,
        std::shared_ptr<EventDispatcher> dispatchers,
        std::shared_ptr<Camera> camera
) : m_producers(std::move(producers)),
    m_renderables(std::move(renderables)),
    m_dispatcher(std::move(dispatchers)),
    m_camera(std::move(camera)) {}
