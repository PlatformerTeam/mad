#ifndef MAD_CORE_RUNNER_GAMERUNNER_HPP
#define MAD_CORE_RUNNER_GAMERUNNER_HPP


namespace mad::core {
    class GameRunner {
    public:
        virtual void run() = 0;

        virtual ~GameRunner() = default;
    };
}


#endif //MAD_CORE_RUNNER_GAMERUNNER_HPP
