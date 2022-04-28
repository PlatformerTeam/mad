#include "Entity.hpp"

#include <event/visual/PositionalAppearance.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <utility>


namespace mad::core {

    mad::core::Entity::Id mad::core::Entity::get_id() const noexcept {
        return m_id;
    }
    Entity::Entity(std::string type) : type(std::move(type)) {}

}
