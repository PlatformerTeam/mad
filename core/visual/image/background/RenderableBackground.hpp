#ifndef MAD_RENDERABLEBACKGROUND_HPP
#define MAD_RENDERABLEBACKGROUND_HPP

#include <visual/Renderable.hpp>
#include <visual/image/background/BackgroundImage.hpp>

#include <common/FVec2D.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace mad::core {

    class RenderableBackground : public Renderable {
    public:
        RenderableBackground(const std::shared_ptr<BackgroundImage> &background, std::shared_ptr<Vec2d> position,
                             std::shared_ptr<float> rotation);

        bool render(sf::RenderWindow &window) override;


    private:
        sf::Texture m_texture;

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

        float m_parallax_ratio;
    };

}

#endif //MAD_RENDERABLEBACKGROUND_HPP
