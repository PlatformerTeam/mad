#ifndef MAD_CONDITION_HPP
#define MAD_CONDITION_HPP

#include <event/Event.hpp>
#include <unordered_set>
namespace mad::core {
    struct Condition {
    public:
        virtual bool is_triggered_by(const mad::core::Event &event) = 0;
        virtual std::unordered_set<Event::Type> triggers() = 0;

    private:
    };
}// namespace mad::core


#endif//MAD_CONDITION_HPP
