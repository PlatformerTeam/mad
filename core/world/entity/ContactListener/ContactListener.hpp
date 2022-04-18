#ifndef MAD_CONTACTLISTENER_HPP
#define MAD_CONTACTLISTENER_HPP

#include <box2d/b2_world_callbacks.h>
#include <world/entity/PhysicalEntity.hpp>
#include <common/Cast.hpp>
#include <event/physics/Collision.hpp>

namespace mad::core{
    class MyContactListener : public b2ContactListener {
        void BeginContact(b2Contact *contact) override {

            b2BodyUserData dataA = contact->GetFixtureA()->GetBody()->GetUserData();
            b2BodyUserData dataB = contact->GetFixtureB()->GetBody()->GetUserData();
            //std::cout << "!!! " << dataA.pointer <<  "\n";
            dispatcher.dispatch(std::make_shared<Collision>(dataA.pointer, dataB.pointer));

            /*if (cast_to_or_null<PhysicalEntity>(dataA.pointer) != nullptr) {
                PhysicalEntity* physical_entity = *dataA.pointer;

            }*/

        }

        void EndContact(b2Contact* contact) override{

            /*//check if fixture A was a ball
            void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
            if ( bodyUserData )
                static_cast<Ball*>( bodyUserData )->endContact();

            //check if fixture B was a ball
            bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
            if ( bodyUserData )
                static_cast<Ball*>( bodyUserData )->endContact();*/

        }

    public:
        MyContactListener(mad::core::EventDispatcher &dispatcher) : b2ContactListener(), dispatcher(dispatcher){

        }

    private:
        mad::core::EventDispatcher &dispatcher;
    };

}


#endif//MAD_CONTACTLISTENER_HPP
