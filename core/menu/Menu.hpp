#ifndef MAD_MENU_HPP
#define MAD_MENU_HPP

#include <event/management/dispatcher/DelayedDispatcher.hpp>
#include <event/management/producer/EventProducer.hpp>
#include <event/menu/MenuEvent.hpp>
#include <visual/Renderable.hpp>

#include <memory>


namespace mad::core {

    class Menu : public Renderable, public EventProducer {
    protected:
        enum class Type {
            Pause,
            Main,
        };

    private:
        std::shared_ptr<DelayedDispatcher> m_event_dispatcher;
        Menu::Type m_menu_type;

    public:
        Menu(Menu::Type type, std::shared_ptr<DelayedDispatcher> dispatcher);

        virtual void process_menu_event(std::shared_ptr<MenuEvent> menu_event) = 0;

        virtual ~Menu() = default;
    };

}

#endif//MAD_MENU_HPP
