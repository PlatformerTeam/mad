#ifndef MAD_SYSTEMLISTENER_HPP
#define MAD_SYSTEMLISTENER_HPP

#include <event/management/EventProducer.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <map>
#include <vector>

namespace mad::core {

    class SystemListener : public EventProducer {
    public:
        explicit SystemListener(std::shared_ptr<sf::RenderWindow> window);

        void produce(EventDispatcher &dispatcher) override;

    private:
        std::shared_ptr<sf::RenderWindow> m_window;
        std::map<sf::Keyboard::Key, bool> m_key_is_free;
        std::vector<sf::Keyboard::Key> m_candidate_held_keys {
            sf::Keyboard::Key::Up,
            sf::Keyboard::Key::Down,
            sf::Keyboard::Key::Left,
            sf::Keyboard::Key::Right,
        };
    };

}


#endif //MAD_SYSTEMLISTENER_HPP
