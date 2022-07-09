#ifndef MAD_SENSORCOLLISIONEND_HPP
#define MAD_SENSORCOLLISIONEND_HPP

#include "event/Event.hpp"
namespace mad::core {

    struct SensorCollisionEnd : public Event {
        explicit SensorCollisionEnd(int m_id);

        const int m_id;
    };

}


#endif//MAD_SENSORCOLLISIONEND_HPP
