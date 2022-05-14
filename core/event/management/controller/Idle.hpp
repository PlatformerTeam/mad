#ifndef MAD_IDLE_HPP
#define MAD_IDLE_HPP
#include "Controller.hpp"

namespace mad::core {

    class Idle : public Controller {
    public:
        explicit Idle();

        void control() override;

    private:

    };

}


#endif//MAD_IDLE_HPP
