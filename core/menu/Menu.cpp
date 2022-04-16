#include "Menu.hpp"

namespace mad::core {

    Menu::Menu(Menu::Type type) : m_menu_type(type) { }

    void Menu::process_menu_event(std::shared_ptr<MenuEvent> menu_event) {
        m_events_queue.push(std::move(menu_event));
    }

    void Menu::produce(EventDispatcher &dispatcher) {
        while (!m_events_queue.empty()) {
            dispatcher.dispatch(std::move(m_events_queue.front()));
            m_events_queue.pop();
        }
    }

}