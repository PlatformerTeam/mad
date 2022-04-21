#include "Collision.hpp"
mad::core::Collision::Collision(int new_first_object_id, int new_second_object_id) : Event(Event::Type::Collision), first_object_id(new_first_object_id), second_object_id(new_second_object_id) {

}
