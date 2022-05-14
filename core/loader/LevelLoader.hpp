#ifndef MAD_LEVELLOADER_HPP
#define MAD_LEVELLOADER_HPP

#include <runner/LevelRunner.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>

#include <utility>

namespace mad::core {

    class LevelLoader {
    public:
        virtual std::unique_ptr<LevelRunner> load(
                std::shared_ptr<EventDispatcher> global_dispatcher,
                std::shared_ptr<SystemListener> system_listener) = 0;

    };
}

#endif //MAD_LEVELLOADER_HPP
