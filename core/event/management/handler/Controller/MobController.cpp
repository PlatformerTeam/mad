#include "MobController.hpp"
#include "world/entity/Mobs/Mob.hpp"
#include <common/Cast.hpp>
#include <common/Color.hpp>
#include <event/Event.hpp>
#include <event/physics/Collision.hpp>
#include <spdlog/spdlog.h>
#include <world/entity/Entity.hpp>
#include <world/entity/PhysicalEntity.hpp>
#include <world/filter/TagFilter.hpp>
#include <world/intent/LambdaIntent.hpp>

mad::core::MobController::MobController() = default;
void mad::core::MobController::handle(const mad::core::Event &event) {
    Controller::handle(event);
}
std::unordered_set<mad::core::Event::Type> mad::core::MobController::handled_types() {
    return Controller::handled_types();
}
void mad::core::MobController::control(EntityStorage &m_storage) {
    for (Entity::Id entity_id : m_storage.extract(TagFilter(Entity::Type::Enemy))) {
        if (&m_storage.get_entity(entity_id) != nullptr && cast_to_or_null<Mob>(m_storage.get_entity(entity_id)) != nullptr) {
            auto mob = cast_to_or_null<Mob>(m_storage.get_entity(entity_id));
            mob->set_image_color(Color(200, 200, rand() % 256));
        }
    }
}
