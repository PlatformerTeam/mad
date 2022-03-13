#ifndef MAD_SYSTEMLISTENER_H
#define MAD_SYSTEMLISTENER_H

#include <event/management/EventProducer.hpp>
#include <event/management/EventDispatcher.hpp>

// SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

namespace mad::core {

    class SystemListener : public EventProducer {
    public:
        SystemListener();

        explicit SystemListener(std::shared_ptr<sf::RenderWindow> window);

        void produce(EventDispatcher &dispatcher) override;

    private:
        std::shared_ptr<sf::RenderWindow> m_window = nullptr;
    };

}


#endif //MAD_SYSTEMLISTENER_H
