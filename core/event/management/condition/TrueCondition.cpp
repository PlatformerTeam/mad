#include "TrueCondition.hpp"

bool mad::core::TrueCondition::is_triggered_by(const mad::core::Event &event) {
    return true;
}
std::unordered_set<mad::core::Event::Type> mad::core::TrueCondition::triggers() {
    return {mad::core::Event::Type::KeyPressed};
}