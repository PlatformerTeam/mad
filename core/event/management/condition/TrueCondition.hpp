#ifndef MAD_TRUECONDITION_HPP
#define MAD_TRUECONDITION_HPP

#include "Condition.hpp"
namespace mad::core {
    struct TrueCondition : Condition {
    public:
        TrueCondition() = default;
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
    };
}// namespace mad::core

#endif//MAD_TRUECONDITION_HPP
