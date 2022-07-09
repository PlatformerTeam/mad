#ifndef MAD_CORE_WORLD_WORLD_HPP
#define MAD_CORE_WORLD_WORLD_HPP


#include <event/management/producer/EventProducer.hpp>
#include <world/entity/Entity.hpp>
#include <visual/image/shape/Shape.hpp>
#include <visual/image/storage/ImageStorage.hpp>

#include <common/FVec2D.hpp>

#include <memory>

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

        [[nodiscard]] virtual Entity &get_entity(Entity::Id id) noexcept = 0;

        virtual Entity::Id create_viewable_entity(int z_ind,
                                                  Vec2d initial_position, float initial_rotation,
                                                  std::shared_ptr<ImageStorage> image_storage) = 0;

        virtual Entity::Id create_physical_entity(int z_ind, Vec2d initial_position, float initial_rotation,
                                                  std::shared_ptr<ImageStorage> image_storage,
                                                  bool is_fixed, bool is_rotated, uint16 categoryBits = 0x0002, uint16 maskBits = 0x0002) = 0;
    };

}// namespace mad::core


#endif//MAD_CORE_WORLD_WORLD_HPP
