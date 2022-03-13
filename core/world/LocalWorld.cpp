#include "LocalWorld.hpp"
#include "world/entity/Entity.hpp"

#include <common/Error.hpp>
#include <vector>

namespace mad::core {
    class FilterId;
};


bool mad::core::LocalWorld::manipulate(const mad::core::Filter &filter, const mad::core::Intent &intent) {
    //CHECK_THROW(is_legal(validate_filter(f), IllegalManipulation, "Illegal filter");
    //CHECK_THROW(is_legal(validate_intent(i), IllegalManipulation, "Illegal intent");
    std::vector<Entity *> entities;// пока хз как его из фильтра получить
    for (Entity *el: entities) {
        el->accept(*this, const_cast<Intent &>(intent), dispatcher);
    }
    return true;
}
