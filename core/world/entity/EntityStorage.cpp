#include "EntityStorage.hpp"
#include "world/entity/mobs/Mob.hpp"
#include "world/filter/RadiusFilter.hpp"
#include "world/filter/TagRadiusFilter.hpp"
#include "world/filter/TrueFilter.hpp"
#include <common/Error.hpp>
#include <common/FVec2D.hpp>
#include <memory>
#include <visual/image/Image.hpp>
#include <world/filter/TagFilter.hpp>


namespace mad::core {

    std::vector<Entity::Id> EntityStorage::extract(const Filter &filter) {
        switch (filter.type) {
            case Filter::Type::Id: {
                IdFilter id_filter = const_cast_to<IdFilter>(filter);
                return id_filter.get_filter_ids();
            }

            case Filter::Type::True: {
                return m_list_ids;
            }

            case Filter::Type::EntityTag: {
                TagFilter tag_filter = const_cast_to<TagFilter>(filter);
                return m_map_entities_by_tag[tag_filter.get_filter_tag()];
            }

            case Filter::Type::Radius: {
                std::vector<Entity::Id> arr;

                RadiusFilter radius_filter = const_cast_to<RadiusFilter>(filter);
                for (Entity::Id entity_id : extract(TrueFilter())) {
                    if ((&get_entity(entity_id)) != nullptr && cast_to_or_null<PhysicalEntity>(get_entity(entity_id)) != nullptr) {
                        auto physical_entity = cast_to_or_null<PhysicalEntity>(get_entity(entity_id));
                        float t1 = dist_sq(physical_entity->get_position(), radius_filter.get_filter_point());
                        float t2 = radius_filter.get_filter_radius_sq();
                        if (dist_sq(physical_entity->get_position(), radius_filter.get_filter_point()) < radius_filter.get_filter_radius_sq()) {
                            arr.push_back(entity_id);
                        }
                    }
                }
                return arr;
            }

            case Filter::Type::TagRadius: {
                std::vector<Entity::Id> arr;

                auto tag_radius_filter = const_cast_to<TagRadiusFilter>(filter);
                for (Entity::Id entity_id : extract(TrueFilter())) {
                    if ((&get_entity(entity_id)) != nullptr && cast_to_or_null<PhysicalEntity>(get_entity(entity_id)) != nullptr) {
                        auto physical_entity = cast_to_or_null<PhysicalEntity>(get_entity(entity_id));
                        float t1 = dist_sq(physical_entity->get_position(), tag_radius_filter.get_filter_point());
                        float t2 = tag_radius_filter.get_filter_radius_sq();
                        if (dist_sq(physical_entity->get_position(), tag_radius_filter.get_filter_point()) < tag_radius_filter.get_filter_radius_sq() &&
                            physical_entity->tags.find(tag_radius_filter.get_filter_tag()) != physical_entity->tags.end()) {
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

    Entity::Id EntityStorage::create_viewable_entity(std::unordered_set<std::string> tags, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image) {
        auto new_entity_id = static_cast<Entity::Id>(m_map_entities.size());
        m_list_ids.push_back(new_entity_id);
        m_map_entities[new_entity_id] = std::make_unique<ViewableEntity>(tags, new_entity_id, z_ind, initial_position, initial_rotation, image);
        for(const auto& tag : tags){
            m_map_entities_by_tag[tag].push_back(new_entity_id);
        }
        return new_entity_id;
    }
    Entity::Id EntityStorage::create_physical_entity(std::unordered_set<std::string> tags, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, b2World &physicalWorld, bool is_Fixed) {
        auto new_entity_id = static_cast<Entity::Id>(m_map_entities.size());
        m_list_ids.push_back(new_entity_id);
        if (tags.find("SimpleObject") != tags.end()) {
            m_map_entities[new_entity_id] = std::make_unique<PhysicalEntity>(tags, new_entity_id, z_ind, initial_position, initial_rotation, image, physicalWorld, is_Fixed);
        }
        if (tags.find("Enemy") != tags.end() || tags.find("Hero") != tags.end()) {
            m_map_entities[new_entity_id] = std::make_unique<Mob>(tags, new_entity_id, z_ind, initial_position, initial_rotation, image, physicalWorld, is_Fixed);
        }
        for(const auto& tag : tags){
            m_map_entities_by_tag[tag].push_back(new_entity_id);
        }
        return new_entity_id;
    }

}// namespace mad::core
