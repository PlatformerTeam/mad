#include "PauseMenu.hpp"

namespace mad::core {

    PauseMenu::PauseMenu(std::shared_ptr<DelayedDispatcher> dispatcher) : Menu(Menu::Type::Pause, std::move(dispatcher)) { }

}