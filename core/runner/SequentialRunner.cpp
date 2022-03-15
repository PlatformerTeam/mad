#include "SequentialRunner.hpp"

#include <visual/Camera.hpp>

#include <spdlog/spdlog.h>


void mad::core::SequentialRunner::run(sf::RenderWindow &window) {
    while (true) {
        window.clear(sf::Color(0, 0, 0));
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
        std::shared_ptr<EventDispatcher> dispatchers
) : m_producers(std::move(producers)),
    m_renderables(std::move(renderables)),
    m_dispatcher(std::move(dispatchers)) {}
