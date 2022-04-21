#ifndef MAD_CORE_WORLD_WORLD_HPP
#define MAD_CORE_WORLD_WORLD_HPP


#include <event/management/producer/EventProducer.hpp>
#include <common/FVec2D.hpp>
#include <world/entity/Entity.hpp>

#include <memory>
#include "visual/image/shape/Shape.hpp"

namespace mad::core {
    class Filter;

    class Intent;

    class Image;
}// namespace mad::core


namespace mad::core {

    class World : public EventProducer {
    public:
        virtual bool manipulate(const Filter &filter, const Intent &intent) = 0;

        bool manipulate_entity_id(Entity::Id entity_id, const Intent &intent);

        virtual Entity::Id create_viewable_entity(int z_ind,
                                                  Vec2d initial_position, float initial_rotation,
                                                  std::shared_ptr<Image> image) = 0;

        virtual Entity::Id create_physical_entity(int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, bool is_Fixed) = 0;
    };

}// namespace mad::core


#endif//MAD_CORE_WORLD_WORLD_HPP
