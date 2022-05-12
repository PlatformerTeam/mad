#include "TimerCondition.hpp"

mad::core::TimerCondition::TimerCondition(float m_dt) : m_dt(m_dt) {
    sf::Time time = clock.getElapsedTime();
    timerStart = time.asSeconds();
}
bool mad::core::TimerCondition::is_triggered_by(const mad::core::Event &event) {
    return clock.getElapsedTime().asSeconds() - timerStart > m_dt;
}
void mad::core::TimerCondition::on_start() {
    sf::Time time = clock.getElapsedTime();
    timerStart = time.asSeconds();
}
std::unordered_set<mad::core::Event::Type> mad::core::TimerCondition::triggers() {
    return { mad::core::Event::Type::WorldUpdate};
}
