#ifndef MAD_CLOSINGHANDLER_HPP
#define MAD_CLOSINGHANDLER_HPP

#include <event/management/handler/EventHandler.hpp>

#include <runner/Runner.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <spdlog/spdlog.h>

#include <unordered_set>


namespace mad::core {

    class WindowCloseHandler : public EventHandler {
    public:
        explicit WindowCloseHandler(Runner& runner,
                                    sf::RenderWindow& window);

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

    private:
        Runner& m_runner;
        sf::RenderWindow& m_window;
    };

}

#endif //MAD_CLOSINGHANDLER_HPP
