#ifndef MAD_CORE_RUNNER_SEQUENTIALRUNNER_HPP
#define MAD_CORE_RUNNER_SEQUENTIALRUNNER_HPP

#include <runner/Runner.hpp>
#include <event/management/producer/EventProducer.hpp>
#include <visual/Renderable.hpp>

#include <vector>
#include <memory>


namespace mad::core {
    class Camera;
}

namespace mad::core {

    class SequentialRunner : public Runner {
    public:
        explicit SequentialRunner(
                std::vector<std::shared_ptr<EventProducer>> producers,
                std::vector<std::shared_ptr<Renderable>> renderables,
                std::shared_ptr<EventDispatcher> dispatchers
        );

        [[noreturn]] void run(sf::RenderWindow &window) override;

        void stop() override;

    private:
        std::vector<std::shared_ptr<EventProducer>> m_producers;
        std::vector<std::shared_ptr<Renderable>> m_renderables;
        std::shared_ptr<EventDispatcher> m_dispatcher;
        bool m_running;
    };

}


#endif //MAD_CORE_RUNNER_SEQUENTIALRUNNER_HPP
