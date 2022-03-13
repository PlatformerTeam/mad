#ifndef MAD_LAMBDAINTENT_HPP
#define MAD_LAMBDAINTENT_HPP

#include "Intent.hpp"
#include <world/entity/Entity.hpp>

#include <memory>
#include <functional>

namespace mad::core {

    struct LambdaIntent : public Intent {
    public:
        explicit LambdaIntent(std::function<void (const Entity &entity, const EventDispatcher &event_dispatcher)> func);
        void apply(const Entity &entity, const EventDispatcher &event_dispatcher);

    private:
        std::function<void (const Entity &entity, const EventDispatcher &event_dispatcher)> m_func;
    };

}

#endif //MAD_LAMBDAINTENT_HPP
