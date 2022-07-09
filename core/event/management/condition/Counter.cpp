#include "Counter.hpp"
mad::core::Counter::Counter(int *c, int mx) : c(c), mx(mx){
}
bool mad::core::Counter::is_triggered_by(const mad::core::Event &event) {
    return *c >= mx;
}
std::unordered_set<mad::core::Event::Type> mad::core::Counter::triggers() {
    return {Event::Type::WorldUpdate};
}
void mad::core::Counter::on_start() {
}
