#ifndef MAD_TIMERCONDITION_HPP
#define MAD_TIMERCONDITION_HPP

#include "Condition.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
namespace mad::core {
    struct TimerCondition : Condition {
    public:
        explicit TimerCondition(float m_dt);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        sf::Clock clock;
        float timerStart;
        float m_dt;
    };
}// namespace mad::core


#endif//MAD_TIMERCONDITION_HPP
