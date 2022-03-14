#include "Entity.hpp"

namespace mad::core {

    mad::core::Entity::Id mad::core::Entity::get_id() const noexcept {
        return m_id;
    }

    void Entity::appear(const EventDispatcher &) const {
        NOT_IMPLEMENTED
    }

}
