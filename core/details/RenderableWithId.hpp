#ifndef MAD_RENDERABLEWITHID_HPP
#define MAD_RENDERABLEWITHID_HPP

#include <visual/Renderable.hpp>
#include <world/entity/Entity.hpp>
#include <utility>

namespace mad::core {

    struct RenderableWithId {

        std::shared_ptr<Renderable> m_renderable;

        Entity::Id m_entity_id;

        RenderableWithId(std::shared_ptr<Renderable> renderable, Entity::Id entity_id)
                        : m_renderable(std::move(renderable)), m_entity_id(entity_id) {
        }
    };

}

#endif //MAD_RENDERABLEWITHID_HPP
