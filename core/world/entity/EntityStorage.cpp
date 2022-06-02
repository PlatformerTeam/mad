

#include <common/Error.hpp>
#include <common/FVec2D.hpp>
#include <visual/image/Image.hpp>
#include <memory>
#include "EntityStorage.hpp"


namespace mad::core {

    std::vector<Entity::Id> EntityStorage::extract(const Filter &filter) const {
        switch (filter.type) {
            case Filter::Type::Id: {
                IdFilter id_filter = const_cast_to<IdFilter>(filter);
                return id_filter.get_filter_ids();
            }

            case Filter::Type::True: {
                return m_list_ids;
            }
        }
    }

    Entity &EntityStorage::get_entity(Entity::Id id) {
        auto entity_it = m_map_entities.find(id);
        CHECK_THROW(entity_it != m_map_entities.end(), InvalidArgument, "Entity with given id does not exist");
        return *entity_it->second;
    }

    Entity::Id EntityStorage::create_viewable_entity(int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<ImageStorage> image_storage) {
        auto new_entity_id = static_cast<Entity::Id>(m_map_entities.size());
        m_list_ids.push_back(new_entity_id);
        m_map_entities[new_entity_id] = std::make_unique<ViewableEntity>(new_entity_id, z_ind, initial_position, initial_rotation, image_storage);
        return new_entity_id;
    }

    Entity::Id EntityStorage::create_physical_entity(int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<ImageStorage> image_storage,
                                                     b2World &physicalWorld, bool is_fixed, bool is_rotated, uint16 categoryBits, uint16 maskBits) {
        auto new_entity_id = static_cast<Entity::Id>(m_map_entities.size());
        m_list_ids.push_back(new_entity_id);
        m_map_entities[new_entity_id] = std::make_unique<PhysicalEntity>(new_entity_id, z_ind, initial_position, initial_rotation,
                                                                         image_storage, physicalWorld, is_fixed, is_rotated,  categoryBits,  maskBits);
        return new_entity_id;
    }

}// namespace mad::core
