#include "ViewableEntity.hpp"

#include <common/Cast.hpp>
#include <event/visual/PositionalAppearance.hpp>
#include <event/visual/VisualEvent.hpp>
#include <world/intent/LambdaIntent.hpp>
#include <utility>

#include <spdlog/spdlog.h>


void mad::core::ViewableEntity::accept(World &world, const Intent &intent, EventDispatcher &dispatcher) {
    cast_to<const LambdaIntent>(intent).apply(*this, dispatcher);
}

mad::core::Vec2d mad::core::ViewableEntity::get_image_position() {
    return *m_position;
}

void mad::core::ViewableEntity::set_image_position(mad::core::Vec2d new_position) {
    *m_position = new_position;
}

void mad::core::ViewableEntity::set_image_rotation(float new_rotation) {
    *m_rotation = new_rotation;
}

void mad::core::ViewableEntity::set_image_color(Color color) {
    if (m_image->type == Image::Type::Shape) {
        auto shape = mad::core::pointer_cast_to<mad::core::Shape>(m_image);
        shape->set_color(color);
    }
}

void mad::core::ViewableEntity::move(mad::core::Vec2d move_delta) {
    *m_position += move_delta;
}

void mad::core::ViewableEntity::appear(mad::core::EventDispatcher &dispatcher) const {
    SPDLOG_DEBUG("create positional appearance");
    dispatcher.dispatch(std::make_shared<PositionalAppearance>(m_position, m_rotation, m_image, m_z_ind));
}

mad::core::ViewableEntity::ViewableEntity(std::string e_type,
                                          mad::core::ViewableEntity::Id id,
                                          int z_ind,
                                          Vec2d initial_position,
                                          float initial_rotation,
                                          std::shared_ptr<Image> image)
    : Entity(std::move(e_type)),
      m_id(id),
      m_z_ind(z_ind),
      m_position(std::make_shared<Vec2d>(initial_position)),
      m_rotation(std::make_shared<float>(initial_rotation)),
      m_image(std::move(image)) {
}
