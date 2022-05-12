#ifndef MAD_WORLDUPDATE_HPP
#define MAD_WORLDUPDATE_HPP


#include "Event.hpp"
namespace mad::core {

    struct WorldUpdate : public Event {
        explicit WorldUpdate();

    };

}

#endif//MAD_WORLDUPDATE_HPP
