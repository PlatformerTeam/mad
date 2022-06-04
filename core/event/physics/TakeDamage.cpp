#include "TakeDamage.hpp"

mad::core::TakeDamage::TakeDamage(int entity_id) : Event(Event::Type::TakeDamage), entity_id(entity_id) {
    //SPDLOG_INFO("handle collision {0} {1}", first_object_id, second_object_id);
}
