#ifndef MAD_RENDERABLEDECORATIONIMAGE_HPP
#define MAD_RENDERABLEDECORATIONIMAGE_HPP

#include <visual/Renderable.hpp>
#include <visual/image/decoration/DecorationImage.hpp>

#include <common/FVec2D.hpp>

#include <SFML/Graphics.hpp>

namespace mad::core {

    class RenderableDecoration : public Renderable {
    public:
        RenderableDecoration(const std::shared_ptr<DecorationImage>& decoration_image, std::shared_ptr<Vec2d> position,
                             std::shared_ptr<float> rotation);

        bool render(sf::RenderWindow &window) override;

        sf::RectangleShape get_physical_shape() noexcept override;

    private:
        sf::Texture m_texture;

        Vec2d m_scale = {1, 1};

        float m_delta_x;

        float m_delta_y;

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

    };

}

#endif //MAD_RENDERABLEDECORATIONIMAGE_HPP
