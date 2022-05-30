#include "CollisionCondition.hpp"

#include <common/Cast.hpp>
#include <event/physics/Collision.hpp>


namespace mad::core {

    CollisionCondition::CollisionCondition(int first_object_id, int second_object_id) : m_first_object_id(first_object_id), m_second_object_id(second_object_id) { }

    bool CollisionCondition::is_triggered_by(const Event &event) {
        const auto &collision = const_cast_to<Collision>(event);
        return (m_first_object_id == collision.first_object_id && m_second_object_id == collision.second_object_id) ||
               (m_first_object_id == collision.second_object_id && m_second_object_id == collision.first_object_id);
    }

    std::unordered_set<Event::Type> CollisionCondition::triggers() {
        return {Event::Type::Collision};
    }

    void CollisionCondition::on_start() {
    }

}
