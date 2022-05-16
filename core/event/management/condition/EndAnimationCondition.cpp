#include "EndAnimationCondition.hpp"
#include "common/Cast.hpp"
#include <event/action/EndOfRenderAction.hpp>
mad::core::EndAnimationCondition::EndAnimationCondition(Entity::Id m_entity_id, ImageStorage::TypeAction m_type_action) : m_entity_id(m_entity_id), m_type_action(m_type_action){
}
bool mad::core::EndAnimationCondition::is_triggered_by(const mad::core::Event &event) {
    auto e = const_cast_to<EndOfRenderAction>(event);
    return m_entity_id == e.get_entity_id() && m_type_action == e.get_type_action();
}
std::unordered_set<mad::core::Event::Type> mad::core::EndAnimationCondition::triggers() {
    return {mad::core::Event::Type::EndOfRenderAction};
}
void mad::core::EndAnimationCondition::on_start() {

}
