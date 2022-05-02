#ifndef MAD_CONTROLLER_HPP
#define MAD_CONTROLLER_HPP

#include <world/entity/EntityStorage.hpp>
#include <event/management/handler/EventHandler.hpp>
namespace mad::core {

    class Controller : public EventHandler {
    public:
        explicit Controller(std::shared_ptr<EntityStorage> m_storage);

        void handle(const Event &event) override;

        virtual void control() = 0;

    protected:
        std::shared_ptr<EntityStorage> m_storage;
    };

}
#endif//MAD_CONTROLLER_HPP
