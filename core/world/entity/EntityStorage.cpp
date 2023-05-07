

#include "EntityStorage.hpp"
#include "algorithm"
#include "world/filter/RadiusFilter.hpp"
#include "world/filter/TrueFilter.hpp"
#include <common/Error.hpp>
#include <common/FVec2D.hpp>
#include <memory>
#include <visual/image/Image.hpp>



namespace mad::core {
    float dist_sq(const Vec2d &v1, const Vec2d &v2) {
        return (v1.get_x() - v2.get_x()) * (v1.get_x() - v2.get_x()) + (v1.get_y() - v2.get_y()) * (v1.get_y() - v2.get_y());
    }

    std::vector<Entity::Id> EntityStorage::extract(const Filter &filter) {
        switch (filter.type) {
            case Filter::Type::Id: {
                IdFilter id_filter = const_cast_to<IdFilter>(filter);
                return id_filter.get_filter_ids();
            }

            case Filter::Type::True: {
                return m_list_ids;
            }

            case Filter::Type::Radius: {
                std::vector<Entity::Id> arr;

                RadiusFilter radius_filter = const_cast_to<RadiusFilter>(filter);
                for (Entity::Id entity_id : extract(TrueFilter())) {
                    if (auto physical_entity = cast_to_or_null<PhysicalEntity>(get_entity(entity_id))) {
                        if (dist_sq(physical_entity->get_position(), radius_filter.get_filter_point()) < radius_filter.get_filter_radius_sq()) {
                            arr.push_back(entity_id);
                        }
                    }
                }
                return arr;
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

    void EntityStorage::destroy_physical_entity(Entity::Id entity_id) {
        m_list_ids.erase(std::remove(m_list_ids.begin(), m_list_ids.end(), entity_id), m_list_ids.end());
        m_map_entities[entity_id] = nullptr;
    }


}// namespace mad::core
