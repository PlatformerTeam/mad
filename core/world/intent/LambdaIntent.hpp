#ifndef MAD_LAMBDAINTENT_HPP
#define MAD_LAMBDAINTENT_HPP

#include "Intent.hpp"
#include <world/entity/Entity.hpp>

#include <memory>
#include <functional>

namespace mad::core {

    struct LambdaIntent : public Intent {
    public:
        explicit LambdaIntent(std::function<void(Entity &entity, EventDispatcher &event_dispatcher)> func);

        void apply(Entity &entity, EventDispatcher &event_dispatcher) const;

    private:
        std::function<void(Entity &entity, EventDispatcher &event_dispatcher)> m_func;
    };

}

#endif //MAD_LAMBDAINTENT_HPP
