#ifndef MAD_MOBCONTROLLER_HPP
#define MAD_MOBCONTROLLER_HPP


#include "Controller.hpp"
namespace mad::core {

    class MobController : public Controller {
    public:
        explicit MobController();

        void handle(const Event &event) override;

        std::unordered_set<Event::Type> handled_types() override;

        void control(EntityStorage &m_storage) override;

    private:
    };

}// namespace mad::core


#endif//MAD_MOBCONTROLLER_HPP
