#include "ViewableEntity.hpp"
#include "common/Cast.hpp"
#include "event/visual/VisualEvent.hpp"
#include "world/intent/LambdaIntent.hpp"
#include <event/visual/PositionalAppearance.hpp>


void mad::core::ViewableEntity::accept(World &world, const Intent &intent, EventDispatcher &dispatcher) {
    cast_to<const LambdaIntent>(intent).apply(*this, dispatcher);
}

mad::core::Vec2d mad::core::ViewableEntity::get_image_position() {
    return *m_position;
}

void mad::core::ViewableEntity::set_image_position(mad::core::Vec2d new_position) {
    *m_position = new_position;
}

void mad::core::ViewableEntity::move(mad::core::Vec2d move_delta) {
    *m_position += move_delta;
}

void mad::core::ViewableEntity::appear(mad::core::EventDispatcher &dispatcher) const {
    dispatcher.dispatch(std::make_shared<Event>(PositionalAppearance(m_position, m_image, m_id)));
}

mad::core::ViewableEntity::ViewableEntity(mad::core::ViewableEntity::Id id,
                                          int z_ind,
                                          Vec2d initial_position,
                                          std::shared_ptr<Image> image)
        : m_id(id),
          m_z_ind(z_ind),
          m_position(std::make_shared<Vec2d>(initial_position)),
          m_image(std::move(image)) {
}
