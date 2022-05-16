#ifndef MAD_CORE_VISUAL_RENDERABLE_HPP
#define MAD_CORE_VISUAL_RENDERABLE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <visual/image/Image.hpp>

#include <imgui.h>
#include <imgui-SFML.h>
#include <common/Error.hpp>

#include <memory>

namespace mad::core {

    class Renderable {
    public:
        virtual bool render(sf::RenderWindow &window) = 0;

        std::shared_ptr<bool> is_active;

        std::shared_ptr<Image::Orientation> m_orientation;
    };
}


#endif //MAD_CORE_VISUAL_RENDERABLE_HPP
