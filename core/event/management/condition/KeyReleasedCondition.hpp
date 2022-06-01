#ifndef MAD_KEYRELEASEDCONDITION_HPP
#define MAD_KEYRELEASEDCONDITION_HPP

#include "Condition.hpp"
namespace mad::core {
    struct KeyReleasedCondition : Condition {
    public:
        explicit KeyReleasedCondition(int m_key_id);
        bool is_triggered_by(const mad::core::Event &event) override;
        std::unordered_set<Event::Type> triggers() override;
        void on_start() override;

    private:
        const int m_key_id;
    };
}// namespace mad::core

#endif//MAD_KEYRELEASEDCONDITION_HPP
