#include "PhysicalEntity.hpp"

#include <visual/image/shape/square/Square.hpp>
#include <world/intent/LambdaIntent.hpp>

#include <common/Cast.hpp>

#include <utility>

mad::core::PhysicalEntity::PhysicalEntity(std::int32_t id, int z_ind, Vec2d initial_position, float initial_rotation, std::shared_ptr<ImageStorage> image_storage,
                                          b2World &physicalWorld, bool is_fixed, bool is_rotated)
    : ViewableEntity(id, z_ind, initial_position, initial_rotation, image_storage) {

    //rect.setOrigin(300, 50);

    if(is_fixed)
    {
        b2BodyDef fixedBodyDef;
        fixedBodyDef.position.Set(initial_position.get_x(), initial_position.get_y());
        body = physicalWorld.CreateBody(&fixedBodyDef);
        b2PolygonShape groundBox = (image_storage->get_action(ImageStorage::TypeAction::Idle))->as_fixture();
        body->CreateFixture(&groundBox, 0.0f);
        body->SetTransform(body->GetPosition(), initial_rotation);
    }
    else
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(initial_position.get_x(), initial_position.get_y());
        body = physicalWorld.CreateBody(&bodyDef);
        b2PolygonShape dynamicBox = (image_storage->get_action(ImageStorage::TypeAction::Idle))->as_fixture();

        if (!is_rotated) {
            set_fixed_rotation(true);
        }

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 50.0f;
        fixtureDef.restitution = 0.0f;
        body->SetLinearDamping(0.0000000001);
        body->SetAngularDamping(0);

        body->CreateFixture(&fixtureDef);
        body->SetTransform(body->GetPosition(), initial_rotation);
    }

    body->GetUserData().pointer = m_id;


}
void mad::core::PhysicalEntity::accept(mad::core::World &world, const mad::core::Intent &intent, mad::core::EventDispatcher &dispatcher) {
    cast_to<const LambdaIntent>(intent).apply(*this, dispatcher);
}

void mad::core::PhysicalEntity::rotate(float angle, mad::core::EventDispatcher &dispatcher) {
    NOT_IMPLEMENTED
}
void mad::core::PhysicalEntity::synchronize_position_with_viewable() {
    set_image_position(Vec2d(body->GetPosition().x, body->GetPosition().y));
    set_image_rotation(body->GetAngle() * (180 / M_PI));
}

void mad::core::PhysicalEntity::apply_linear_impulse_to_center(mad::core::Vec2d impulse, mad::core::EventDispatcher &dispatcher, bool awake) {
    body->ApplyLinearImpulseToCenter(impulse, awake);
}
void mad::core::PhysicalEntity::apply_force_to_center(mad::core::Vec2d force, mad::core::EventDispatcher &dispatcher, bool awake) {
    body->ApplyForceToCenter(force, awake);
}
void mad::core::PhysicalEntity::set_linear_velocity(mad::core::Vec2d velocity, mad::core::EventDispatcher &dispatcher) {
    body->SetLinearVelocity(velocity);
}
void mad::core::PhysicalEntity::set_linear_horizontal_velocity(float velocity, mad::core::EventDispatcher &dispatcher) {
    body->SetLinearVelocity({velocity, body->GetLinearVelocity().y});
}

void mad::core::PhysicalEntity::apply_angular_impulse(float impulse, mad::core::EventDispatcher &dispatcher, bool awake) {
    body->ApplyAngularImpulse(impulse, awake);
}
void mad::core::PhysicalEntity::set_transform(mad::core::Vec2d position, float angle) {
    body->SetTransform(position, angle);
}
mad::core::Vec2d mad::core::PhysicalEntity::get_position() {
    return {body->GetPosition().x, body->GetPosition().y};
}
float mad::core::PhysicalEntity::get_angle() {
    return body->GetAngle();
}
void mad::core::PhysicalEntity::apply_torque(float torque, mad::core::EventDispatcher &dispatcher, bool awake) {
    body->ApplyTorque(torque, awake);
}
float mad::core::PhysicalEntity::get_mass() {
    return body->GetMass();
}
void mad::core::PhysicalEntity::set_angular_velocity(float velocity, mad::core::EventDispatcher &dispatcher) {
    body->SetAngularVelocity(velocity);
}
void mad::core::PhysicalEntity::apply_linear_impulse(mad::core::Vec2d impulse, mad::core::Vec2d point, mad::core::EventDispatcher &dispatcher, bool awake) {
    body->ApplyLinearImpulse(impulse, point, awake);
}
void mad::core::PhysicalEntity::apply_force(mad::core::Vec2d force, mad::core::Vec2d point, mad::core::EventDispatcher &dispatcher, bool awake) {
    body->ApplyForce(force, point, awake);
}
void mad::core::PhysicalEntity::set_linear_damping(float linear_damping, mad::core::EventDispatcher &dispatcher) {
    body->SetLinearDamping(linear_damping);
    set_action(ImageStorage::TypeAction::Run);
}
void mad::core::PhysicalEntity::set_angular_damping(float angular_damping, mad::core::EventDispatcher &dispatcher) {
    body->SetAngularDamping(angular_damping);
}
void mad::core::PhysicalEntity::set_gravity_scale(float gravity_scale, mad::core::EventDispatcher &dispatcher) {
    body->SetGravityScale(gravity_scale);
}
float mad::core::PhysicalEntity::get_inertia() {
    return body->GetInertia();
}
mad::core::Vec2d mad::core::PhysicalEntity::get_linear_velocity() {
    return {body->GetLinearVelocity().x, body->GetLinearVelocity().y};
}
float mad::core::PhysicalEntity::get_angular_velocity() {
    return body->GetAngularVelocity();
}
float mad::core::PhysicalEntity::get_linear_damping() {
    return body->GetLinearDamping();
}
float mad::core::PhysicalEntity::get_angular_damping() {
    return body->GetAngularDamping();
}
float mad::core::PhysicalEntity::get_gravity_scale() {
    return body->GetGravityScale();
}
bool mad::core::PhysicalEntity::is_bullet() {
    return body->IsBullet();
}
void mad::core::PhysicalEntity::set_bullet(bool flag) {
    body->SetBullet(flag);
}
bool mad::core::PhysicalEntity::is_awake() {
    return body->IsAwake();
}
void mad::core::PhysicalEntity::set_awake(bool flag) {
    body->SetAwake(flag);
}
bool mad::core::PhysicalEntity::is_enabled() {
    return body->IsEnabled();
}
void mad::core::PhysicalEntity::set_enabled(bool flag) {
    body->SetEnabled(flag);
}
bool mad::core::PhysicalEntity::is_fixed_rotation() {
    return body->IsFixedRotation();
}
void mad::core::PhysicalEntity::set_fixed_rotation(bool flag) {
    body->SetFixedRotation(flag);
}
mad::core::Vec2d mad::core::PhysicalEntity::get_local_center() {
    return {body->GetLocalCenter().x, body->GetLocalCenter().y};
}
mad::core::Vec2d mad::core::PhysicalEntity::get_world_center() {
    return {body->GetWorldCenter().x, body->GetWorldCenter().y};
}
