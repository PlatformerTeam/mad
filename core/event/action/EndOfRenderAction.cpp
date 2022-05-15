#include "EndOfRenderAction.hpp"

namespace mad::core {


    EndOfRenderAction::EndOfRenderAction(Entity::Id entity_id, ImageStorage::TypeAction type_action)
                                        : Event(Event::Type::EndOfRenderAction),
                                          m_entity_id(entity_id), m_type_action(type_action) {
    }

    Entity::Id EndOfRenderAction::get_entity_id() const noexcept {
        return m_entity_id;
    }

    ImageStorage::TypeAction EndOfRenderAction::get_type_action() const noexcept {
        return m_type_action;
    }

}

