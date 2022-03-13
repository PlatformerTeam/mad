//
// Created by mirong on 13.03.2022.
//

#include "ViewableEntity.hpp"
#include "event/visual/VisualEvent.hpp"
#include "world/intent/LambdaIntent.hpp"
#include <event/visual/PositionalAppearance.hpp>
#include "common/Cast.hpp"



void mad::core::ViewableEntity::accept(World &world, const Intent &intent, EventDispatcher &dispatcher) {
    LambdaIntent in1 = cast_to<LambdaIntent>(intent);
    in1.apply(*this, dispatcher);
}

mad::core::Vec2d mad::core::ViewableEntity::get_image_position() {
    return *position;
}

void mad::core::ViewableEntity::set_image_position(mad::core::Vec2d new_position) {
    *position = new_position;
}

void mad::core::ViewableEntity::move(mad::core::Vec2d move_delta) {
    *position += move_delta;
}

void mad::core::ViewableEntity::appear(mad::core::EventDispatcher dispatcher) {
    dispatcher.dispatch(std::make_shared<Event>(PositionalAppearance(position, image, m_id)));
}

