#include "LevelLoader.hpp"

namespace mad::core {

    LevelLoader::LevelLoader(std::shared_ptr<EventDispatcher> dispatcher) : m_global_event_dispatcher(std::move(dispatcher)) { }

    std::unique_ptr<LevelRunner> LevelLoader::load() {
        // TODO
    }

}
