#include "TrueCondition.hpp"

bool mad::core::TrueCondition::is_triggered_by(const mad::core::Event &event) {
    return true;
}
std::unordered_set<mad::core::Event::Type> mad::core::TrueCondition::triggers() {
    return {mad::core::Event::Type::KeyPressed, mad::core::Event::Type::Collision, mad::core::Event::Type::KeyHeld, mad::core::Event::Type::KeyReleased, mad::core::Event::Type::LevelPause, mad::core::Event::Type::Menu, mad::core::Event::Type::Movement, mad::core::Event::Type::Runner, mad::core::Event::Type::Visual, mad::core::Event::Type::WindowClose};
}