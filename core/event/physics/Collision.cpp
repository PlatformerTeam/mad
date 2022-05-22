#include "Collision.hpp"
#include "spdlog/spdlog.h"
mad::core::Collision::Collision(int new_first_object_id, int new_second_object_id) : Event(Event::Type::Collision), first_object_id(new_first_object_id), second_object_id(new_second_object_id) {
    //SPDLOG_INFO("handle collision {0} {1}", first_object_id, second_object_id);
}
