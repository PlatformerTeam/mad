#include "Death.hpp"
mad::core::Death::Death(int entity_id) : Event(Event::Type::Death), entity_id(entity_id) {
}
