#ifndef MAD_LEVELLOADER_HPP
#define MAD_LEVELLOADER_HPP

#include <event/management/dispatcher/EventDispatcher.hpp>
#include <runner/LevelRunner.hpp>

#include <memory>


namespace mad::core {

    class LevelLoader {
    public:
        explicit LevelLoader(std::shared_ptr<EventDispatcher> dispatcher);

        virtual std::unique_ptr<LevelRunner> load() = 0;

    private:
        std::shared_ptr<EventDispatcher> m_global_event_dispatcher;
    };

}

#endif //MAD_LEVELLOADER_HPP
