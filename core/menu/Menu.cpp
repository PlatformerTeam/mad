#include "Menu.hpp"

namespace mad::core {

    Menu::Menu(Menu::Type type, std::shared_ptr<DelayedDispatcher> dispatcher) : m_menu_type(type), m_event_dispatcher(std::move(dispatcher)) { }

}