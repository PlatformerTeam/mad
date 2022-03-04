#ifndef MAD_CORE_WORLD_WORLD_HPP
#define MAD_CORE_WORLD_WORLD_HPP

#include <event/management/EventProducer.hpp>

namespace mad::core {
    class Filter;
    class Intent;
}


namespace mad::core {

    class World : public EventProducer {
    public:
        virtual void manipulate(const Filter &filter, const Intent &intent) = 0;
    };

}


#endif //MAD_CORE_WORLD_WORLD_HPP
