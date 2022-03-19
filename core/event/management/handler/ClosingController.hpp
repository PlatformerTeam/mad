#ifndef MAD_CLOSINGHANDLER_HPP
#define MAD_CLOSINGHANDLER_HPP

#include <event/management/handler/EventHandler.hpp>

#include <runner/SequentialRunner.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <spdlog/spdlog.h>

#include <unordered_set>


namespace mad::core {

    class ClosingController : public EventHandler {
    public:
        explicit ClosingController(std::shared_ptr<SequentialRunner> runner,
                                   std::shared_ptr<sf::RenderWindow> window);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        std::shared_ptr<SequentialRunner> m_runner;
        std::shared_ptr<sf::RenderWindow> m_window;
    };

}

#endif //MAD_CLOSINGHANDLER_HPP
