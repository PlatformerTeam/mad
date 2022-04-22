#ifndef MAD_CORE_VISUAL_RENDERABLE_HPP
#define MAD_CORE_VISUAL_RENDERABLE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

namespace mad::core {

    class Renderable {
    public:
        virtual void render(sf::RenderWindow &window) const = 0;

        [[nodiscard]] virtual int get_unique_number() const noexcept = 0;
    };
}


#endif //MAD_CORE_VISUAL_RENDERABLE_HPP
