#ifndef MAD_LAMBDAINTENT_HPP
#define MAD_LAMBDAINTENT_HPP

#include "Intent.hpp"
#include <world/entity/Entity.hpp>

#include <memory>

namespace mad::core {

    struct LambdaIntent : public Intent {
    public:
        LambdaIntent() : Intent(Intent::Type::Lambda) {
        }

        void fun(const Entity &entity, const EventDispatcher &event_dispatcher) {
        }
    };

}

#endif //MAD_LAMBDAINTENT_HPP
