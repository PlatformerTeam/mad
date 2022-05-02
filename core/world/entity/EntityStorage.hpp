#ifndef MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP
#define MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP

#include "Entity.hpp"

#include <common/Cast.hpp>
#include <common/Error.hpp>
#include <common/FVec2D.hpp>
#include <world/filter/Filter.hpp>
#include <world/filter/IdFilter.hpp>

#include "EntityStorage.hpp"
#include "PhysicalEntity.hpp"
#include "ViewableEntity.hpp"
#include "visual/image/shape/Shape.hpp"

#include <unordered_map>
#include <vector>

namespace mad::core {
    class Image;

    struct EnumClassHash {
        template<typename T>
        std::size_t operator()(T t) const {
            return static_cast<std::size_t>(t);
        }
    };
}// namespace mad::core

namespace mad::core {

    class EntityStorage {
    public:
        [[nodiscard]] std::vector<Entity::Id> extract(const Filter &filter);

        Entity &get_entity(Entity::Id id);

        Entity::Id create_viewable_entity(std::unordered_set<std::string> tags, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image);
        Entity::Id create_physical_entity(std::unordered_set<std::string> tags, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<Image> image, b2World &physicalWorld, bool is_Fixed);

    private:
        std::unordered_map<Entity::Id, std::unique_ptr<Entity>> m_map_entities;
        std::unordered_map<std::string, std::vector<Entity::Id>> m_map_entities_by_tag;
        std::vector<Entity::Id> m_list_ids;
    };

}// namespace mad::core


#endif//MAD_CORE_WORLD_ENTITY_ENTITYSTORAGE_HPP
