#include "EndAnimationCondition.hpp"
#include "common/Cast.hpp"
#include "spdlog/spdlog.h"
#include <event/action/EndOfRenderAction.hpp>
mad::core::EndAnimationCondition::EndAnimationCondition(Entity::Id m_entity_id, ImageStorage::TypeAction m_type_action, int *stage) : m_entity_id(m_entity_id), m_type_action(m_type_action), stage(stage){
}
bool mad::core::EndAnimationCondition::is_triggered_by(const mad::core::Event &event) {
    auto e = const_cast_to<EndOfRenderAction>(event);
    if(m_entity_id == e.get_entity_id() && m_type_action == e.get_type_action()){
        (*stage)++;
        //SPDLOG_DEBUG("current attack_stage {}", *stage);
    }
    //SPDLOG_DEBUG("current attack_stage {}", *stage);
    return m_entity_id == e.get_entity_id() && m_type_action == e.get_type_action();
}
std::unordered_set<mad::core::Event::Type> mad::core::EndAnimationCondition::triggers() {
    return {mad::core::Event::Type::EndOfRenderAction};
}
void mad::core::EndAnimationCondition::on_start() {

}
