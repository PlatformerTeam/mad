#ifndef MAD_CONDITION_HPP
#define MAD_CONDITION_HPP

#include <event/Event.hpp>

#include <memory>
#include <unordered_set>


namespace mad::core {

    class Condition {
    public:
        virtual bool is_triggered_by(const Event &event) = 0;

        virtual std::unordered_set<Event::Type> triggers() = 0;

        virtual void on_start() = 0;

        virtual ~Condition() = default;

        bool triggered;
    };

}

#endif //MAD_CONDITION_HPP
