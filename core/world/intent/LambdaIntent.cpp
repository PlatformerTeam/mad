#include "LambdaIntent.hpp"

#include <utility>

namespace mad::core {

    LambdaIntent::LambdaIntent(
            std::function<void (const Entity &entity,
                    const EventDispatcher &event_dispatcher)> func)
            : Intent(Intent::Type::Lambda),
              m_func(std::move(func)) {
    }

}

