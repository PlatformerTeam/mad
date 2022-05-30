#ifndef MAD_COLLISIONCONDITION_HPP
#define MAD_COLLISIONCONDITION_HPP

#include <event/management/condition/Condition.hpp>


namespace mad::core {

    class CollisionCondition : public Condition {
    public:
        explicit CollisionCondition(int first_object_id, int second_object_id);

        bool is_triggered_by(const mad::core::Event &event) override;

        std::unordered_set<Event::Type> triggers() override;

        void on_start() override;

    private:
        const int m_first_object_id;
        const int m_second_object_id;

    };

}

#endif//MAD_COLLISIONCONDITION_HPP
