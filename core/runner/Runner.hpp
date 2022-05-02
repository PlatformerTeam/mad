#ifndef MAD_CORE_RUNNER_RUNNER_HPP
#define MAD_CORE_RUNNER_RUNNER_HPP

#include <imgui-SFML.h>

namespace mad::core {
    class Runner {
    public:
        virtual void run(sf::RenderWindow &window) = 0;

        virtual void stop() = 0;

        virtual ~Runner() = default;
    };
}


#endif //MAD_CORE_RUNNER_RUNNER_HPP
