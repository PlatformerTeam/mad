#ifndef MAD_SENSORCOLLISION_HPP
#define MAD_SENSORCOLLISION_HPP

#include "event/Event.hpp"
namespace mad::core {

    struct SensorCollision : public Event {
        explicit SensorCollision(int m_id);

        const int m_id;
    };

}

#endif//MAD_SENSORCOLLISION_HPP
