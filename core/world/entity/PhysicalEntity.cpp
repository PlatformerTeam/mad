//
// Created by mirong on 18.03.2022.
//
#include "PhysicalEntity.hpp"
#include "visual/image/shape/Square.hpp"
#include "common/Cast.hpp"
#include "world/intent/LambdaIntent.hpp"

#include <utility>

mad::core::PhysicalEntity::PhysicalEntity(std::int32_t id, int z_ind, Vec2d initial_position, float initial_rotation,std::shared_ptr<Image> image, b2World &physicalWorld, bool is_Fixed)
    : ViewableEntity(id, z_ind, initial_position, initial_rotation, image) {

    //rect.setOrigin(300, 50);

    float side_length = pointer_cast_to<Square>(image)->get_side_length();


    if(is_Fixed){
        b2BodyDef fixedBodyDef;
        fixedBodyDef.position.Set(initial_position.get_x(), initial_position.get_y());
        body = physicalWorld.CreateBody(&fixedBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(side_length / 2, side_length / 2);
        body->CreateFixture(&groundBox, 0.0f);
        body->SetTransform(body->GetPosition(), initial_rotation);
    }
    else{
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(initial_position.get_x(), initial_position.get_y());
        body = physicalWorld.CreateBody(&bodyDef);
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(side_length / 2, side_length / 2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.2f;

        body->CreateFixture(&fixtureDef);
        body->SetTransform(body->GetPosition(), initial_rotation);
    }




}
void mad::core::PhysicalEntity::accept(mad::core::World &world, const mad::core::Intent &intent, mad::core::EventDispatcher &dispatcher) {
    cast_to<const LambdaIntent>(intent).apply(*this, dispatcher);
}
void mad::core::PhysicalEntity::apply_impulse(mad::core::Vec2d impulse, mad::core::EventDispatcher &dispatcher) {
    //body->ApplyForceToCenter(b2Vec2(impulse.get_x(), -impulse.get_y()), true);
    //body->ApplyLinearImpulseToCenter(b2Vec2(impulse.get_x(), impulse.get_y()), true);
    //body->SetLinearVelocity(b2Vec2(impulse.get_x(), impulse.get_y()));
    body->ApplyLinearImpulseToCenter(b2Vec2(impulse.get_x(), -impulse.get_y()), true);
    //body->ApplyAngularImpulse(10, true);
    //body.
}
void mad::core::PhysicalEntity::apply_force(mad::core::Vec2d force, mad::core::EventDispatcher &dispatcher) {
    body->ApplyForceToCenter(b2Vec2(force.get_x(), -force.get_y()), true);
}
void mad::core::PhysicalEntity::rotate(float angle, mad::core::EventDispatcher &dispatcher) {
    NOT_IMPLEMENTED
}
void mad::core::PhysicalEntity::update() {
    set_image_position(Vec2d(body->GetPosition().x, body->GetPosition().y));
    set_image_rotation(body->GetAngle() * (180 / M_PI));
}
