#ifndef MAD_ENDOFRENDERACTION_HPP
#define MAD_ENDOFRENDERACTION_HPP

#include <event/Event.hpp>
#include <world/entity/Entity.hpp>
#include <visual/image/storage/ImageStorage.hpp>

namespace mad::core {

    class EndOfRenderAction : public Event {
    public:
        EndOfRenderAction(Entity::Id entity_id, ImageStorage::TypeAction type_action);

        [[nodiscard]] Entity::Id get_entity_id() const noexcept;

        [[nodiscard]] ImageStorage::TypeAction get_type_action() const noexcept;

    private:
        Entity::Id m_entity_id;

        ImageStorage::TypeAction m_type_action;
    };

}

#endif //MAD_ENDOFRENDERACTION_HPP
