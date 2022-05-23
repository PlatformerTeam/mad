#ifndef MAD_GAMERUNNEREVENTSHANDLER_HPP
#define MAD_GAMERUNNEREVENTSHANDLER_HPP

#include <database/driver/ClientStorageDriver.hpp>
#include <event/management/handler/EventHandler.hpp>
#include <runner/GameRunner.hpp>

#include <spdlog/spdlog.h>
#include <memory>


namespace mad::core {

    class GameRunnerEventsHandler : public EventHandler {
    public:
        explicit GameRunnerEventsHandler(GameRunner& runner, std::shared_ptr<ClientStorageDriver> db_driver);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        GameRunner& m_runner;
        std::shared_ptr<ClientStorageDriver> m_db_driver;

    };

}

#endif //MAD_GAMERUNNEREVENTSHANDLER_HPP
