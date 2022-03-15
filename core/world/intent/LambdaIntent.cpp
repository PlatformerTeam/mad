#include "LambdaIntent.hpp"

#include <utility>

namespace mad::core {

    LambdaIntent::LambdaIntent(
            std::function<void(Entity &entity,
                               EventDispatcher &event_dispatcher)> func)
            : Intent(Intent::Type::Lambda),
              m_func(std::move(func)) {
    }

    void LambdaIntent::apply(Entity &entity, EventDispatcher &event_dispatcher) const {
        m_func(entity, event_dispatcher);
    }

}

