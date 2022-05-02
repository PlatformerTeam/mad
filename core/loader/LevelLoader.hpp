#ifndef MAD_LEVELLOADER_HPP
#define MAD_LEVELLOADER_HPP

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <runner/LevelRunner.hpp>

#include <memory>

#include <nlohmann/json.hpp>

namespace mad::core {

    class LevelLoader {
    public:
        std::unique_ptr<LevelRunner> load(
                std::shared_ptr<EventDispatcher> global_dispatcher,
                std::shared_ptr<SystemListener> system_listener);
    };

}

#endif //MAD_LEVELLOADER_HPP
