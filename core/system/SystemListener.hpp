#ifndef MAD_SYSTEMLISTENER_H
#define MAD_SYSTEMLISTENER_H

#include <event/management/EventProducer.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

namespace mad::core {

    class SystemListener : public EventProducer {
    public:
        explicit SystemListener(std::shared_ptr<sf::RenderWindow> window);

        void produce(EventDispatcher &dispatcher) override;

    private:
        std::shared_ptr<sf::RenderWindow> m_window;
    };

}


#endif //MAD_SYSTEMLISTENER_H
