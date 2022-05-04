#include "Controller.hpp"

#include <event/physics/Collision.hpp>
#include <event/Event.hpp>
#include <event/Event.hpp>
#include <event/physics/Collision.hpp>
#include <event/Event.hpp>
#include <world/entity/Entity.hpp>
#include <world/entity/PhysicalEntity.hpp>
#include <world/intent/LambdaIntent.hpp>

#include <common/Cast.hpp>

#include <spdlog/spdlog.h>

#include <utility>

mad::core::Controller::Controller(std::shared_ptr<EntityStorage> m_storage) : m_storage(std::move(m_storage)) {}

void mad::core::Controller::handle(const mad::core::Event &event) {
}