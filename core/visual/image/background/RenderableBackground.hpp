#ifndef MAD_RENDERABLEBACKGROUND_HPP
#define MAD_RENDERABLEBACKGROUND_HPP

#include <visual/Renderable.hpp>
#include <visual/image/background/BackgroundImage.hpp>

#include <common/FVec2D.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace mad::core {

    class RenderableBackground : public Renderable {
    public:
        RenderableBackground(const std::shared_ptr<BackgroundImage> &background,
                             std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation);

        bool render(sf::RenderWindow &window) override;

        sf::RectangleShape get_physical_shape() noexcept override;

    private:
        std::vector<sf::Texture> m_layers;

        std::shared_ptr<Vec2d> m_camera_position;

        std::vector<Vec2d> m_layers_positions;

        Vec2d m_last_camera_position;

        std::shared_ptr<float> m_rotation;

        Vec2d m_scale = {1, 1};

        std::vector<float> m_parallax_ratios;
    };

}

#endif //MAD_RENDERABLEBACKGROUND_HPP
