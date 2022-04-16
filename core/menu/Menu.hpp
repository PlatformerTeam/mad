#ifndef MAD_MENU_HPP
#define MAD_MENU_HPP

#include <event/management/dispatcher/DelayedDispatcher.hpp>
#include <event/management/producer/EventProducer.hpp>
#include <event/menu/MenuEvent.hpp>
#include <visual/Renderable.hpp>

#include <queue>
#include <memory>


namespace mad::core {

    class Menu : public Renderable, public EventProducer {
    protected:
        enum class Type {
            Pause,
            Main,
        };

    public:
        explicit Menu(Menu::Type type);

        void process_menu_event(std::shared_ptr<MenuEvent> menu_event);

        void produce(EventDispatcher &dispatcher) override;

        virtual ~Menu() = default;

    private:
        std::queue<std::shared_ptr<MenuEvent>> m_events_queue;
        Menu::Type m_menu_type;

    };

}

#endif//MAD_MENU_HPP
