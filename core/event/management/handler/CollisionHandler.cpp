
#include "CollisionHandler.hpp"
#include <spdlog/spdlog.h>
#include <event/physics/Collision.hpp>
#include <common/Cast.hpp>
#include <world/entity/Entity.hpp>
#include <world/entity/PhysicalEntity.hpp>
#include <world/intent/LambdaIntent.hpp>
#include <event/Event.hpp>
mad::core::CollisionHandler::CollisionHandler()= default;


void mad::core::CollisionHandler::handle(const mad::core::Event &event) {
    const auto &collision = const_cast_to<Collision>(event);
    Entity::Id id_A = collision.first_object_id;
    Entity::Id id_B = collision.second_object_id;
    SPDLOG_INFO("handle collision {0} {1}", id_A, id_B);
}
std::unordered_set<mad::core::Event::Type> mad::core::CollisionHandler::handled_types() {
    return {Event::Type::Collision};
}
