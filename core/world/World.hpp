#ifndef MAD_CORE_WORLD_WORLD_HPP
#define MAD_CORE_WORLD_WORLD_HPP

#include <event/management/EventProducer.hpp>
#include <common/FVec2D.hpp>
#include <world/entity/Entity.hpp>


namespace mad::core {
    class Filter;

    class Intent;

    class Image;
}


namespace mad::core {

    class World : public EventProducer {
    public:
        virtual bool manipulate(const Filter &filter, const Intent &intent) = 0;

        bool manipulate_entity_id(Entity::Id entity_id, const Intent &intent);

        virtual Entity::Id create_viewable_entity(int z_ind,
                                                  Vec2d initial_position,
                                                  std::shared_ptr<Image> image) = 0;
    };

}


#endif //MAD_CORE_WORLD_WORLD_HPP
