#ifndef MAD_SYSTEMLISTENER_HPP
#define MAD_SYSTEMLISTENER_HPP

#include <event/management/producer/EventProducer.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <set>

namespace mad::core {

    class SystemListener : public EventProducer {
    public:
        explicit SystemListener(std::shared_ptr<sf::RenderWindow> window);

        void produce(EventDispatcher &dispatcher) override;

    private:
        std::shared_ptr<sf::RenderWindow> m_window;
        std::set<sf::Keyboard::Key> m_key_held;
    };

}


#endif //MAD_SYSTEMLISTENER_HPP
