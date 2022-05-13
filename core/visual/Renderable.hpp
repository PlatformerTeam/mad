#ifndef MAD_CORE_VISUAL_RENDERABLE_HPP
#define MAD_CORE_VISUAL_RENDERABLE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <imgui.h>
#include <imgui-SFML.h>
#include <common/Error.hpp>

namespace mad::core {

    class Renderable {
    public:
        virtual void render(sf::RenderWindow &window) = 0;

        std::shared_ptr<bool> is_active;
    };
}


#endif //MAD_CORE_VISUAL_RENDERABLE_HPP
