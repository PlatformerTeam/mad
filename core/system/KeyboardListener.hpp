#ifndef MAD_CORE_SYSTEM_KEYBOARDLISTENER_HPP
#define MAD_CORE_SYSTEM_KEYBOARDLISTENER_HPP

#include <event/management/EventHandler.hpp>


namespace mad::core {

    class KeyboardListener : public EventHandler {
    public:
        void handle(const Event &event) override;
    };

}


#endif //MAD_CORE_SYSTEM_KEYBOARDLISTENER_HPP
