#include "Controller.hpp"
#include <spdlog/spdlog.h>
#include <event/physics/Collision.hpp>
#include <common/Cast.hpp>
#include <world/entity/Entity.hpp>
#include <world/entity/PhysicalEntity.hpp>
#include <world/intent/LambdaIntent.hpp>
#include <event/Event.hpp>

mad::core::Controller::Controller() = default;

void mad::core::Controller::handle(const mad::core::Event &event) {
}
std::unordered_set<mad::core::Event::Type> mad::core::Controller::handled_types() {
    return {Event::Type::Collision};
}