#ifndef MAD_CORE_RUNNER_GAMERUNNER_HPP
#define MAD_CORE_RUNNER_GAMERUNNER_HPP

#include <imgui-SFML.h>

namespace mad::core {
    class GameRunner {
    public:
        virtual void run(sf::RenderWindow &window) = 0;

        virtual void stop() = 0;

        virtual ~GameRunner() = default;
    };
}


#endif //MAD_CORE_RUNNER_GAMERUNNER_HPP
