#include "MobController.hpp"

#include "event/Event.hpp"
#include "event/physics/Collision.hpp"
#include "event/system/KeyPressed.hpp"
#include "world/entity/Entity.hpp"
#include "world/entity/PhysicalEntity.hpp"
#include "world/entity/mobs/Mob.hpp"
#include "world/filter/RadiusFilter.hpp"
#include "world/filter/TagFilter.hpp"
#include "world/filter/TagRadiusFilter.hpp"
#include "world/intent/LambdaIntent.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "common/Cast.hpp"
#include "common/Color.hpp"

#include "spdlog/spdlog.h"

#include <utility>


mad::core::MobController::MobController(std::shared_ptr<EntityStorage> m_storage) : Controller(std::move(m_storage)){}
void mad::core::MobController::handle(const mad::core::Event &event) {
    if (event.type == mad::core::Event::Type::KeyPressed) {
        const auto &keystroke = mad::core::const_cast_to<mad::core::KeyPressed>(event);
        if (keystroke.key_id == sf::Keyboard::Key::Q) {
            for (Entity::Id entity_id : m_storage->extract(TagFilter("Hero"))) {
                if (cast_to_or_null<Mob>(m_storage->get_entity(entity_id)) != nullptr) {
                    auto hero = cast_to_or_null<Mob>(m_storage->get_entity(entity_id));
                    if(m_storage->extract(TagRadiusFilter(hero->get_position(), 200.0f, "Enemy")).size() > 0){
                        auto mob = cast_to_or_null<Mob>(m_storage->get_entity(m_storage->extract(TagRadiusFilter(hero->get_position(), 200.0f, "Enemy"))[0]));
                        mob->set_image_color(Color(rand() % 256, rand() % 256, rand() % 256));
                    }
                }
            }
        }
    }
}
void mad::core::MobController::control() {
    for (Entity::Id entity_id : m_storage->extract(TagFilter("Enemy"))) {
        if (cast_to_or_null<Mob>(m_storage->get_entity(entity_id)) != nullptr) {
            auto mob = cast_to_or_null<Mob>(m_storage->get_entity(entity_id));
            if(m_storage->extract(TagRadiusFilter(mob->get_position(), 100.0f, "Hero")).size() > 0){
                auto hero = cast_to_or_null<Mob>(m_storage->get_entity(m_storage->extract(TagRadiusFilter(mob->get_position(), 100.0f, "Hero"))[0]));
                hero->set_image_color(Color(rand() % 256, rand() % 256, rand() % 256));
            }
        }
    }
}

std::unordered_set<mad::core::Event::Type> mad::core::MobController::handled_types() {
    return {Event::Type::Collision, Event::Type::KeyPressed};
}
