#ifndef MAD_CORE_RUNNER_SEQUENTIALRUNNER_HPP
#define MAD_CORE_RUNNER_SEQUENTIALRUNNER_HPP

#include <runner/GameRunner.hpp>
#include <event/management/EventProducer.hpp>
#include <visual/Renderable.hpp>

#include <vector>
#include <memory>


namespace mad::core {

    class SequentialRunner : public GameRunner {
    public:
        explicit SequentialRunner(
                std::vector<std::shared_ptr<EventProducer>> producers,
                std::vector<std::shared_ptr<Renderable>> renderables,
                std::shared_ptr<EventDispatcher> dispatchers
        );

        void run() override;

    public:

    private:
        std::vector<std::shared_ptr<EventProducer>> m_producers;
        std::vector<std::shared_ptr<Renderable>> m_renderables;
        std::shared_ptr<EventDispatcher> m_dispatcher;
    };

}


#endif //MAD_CORE_RUNNER_SEQUENTIALRUNNER_HPP
