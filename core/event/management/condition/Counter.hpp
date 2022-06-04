#ifndef MAD_COUNTER_HPP
#define MAD_COUNTER_HPP

#include "Condition.hpp"
namespace mad::core {
    struct Counter : Condition {
    public:
        Counter(int *c, int mx);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        int *c;
        int mx;
    };
}// namespace mad::core


#endif//MAD_COUNTER_HPP
