#ifndef MAD_RENDERABLESTATIC_HPP
#define MAD_RENDERABLESTATIC_HPP

#include <visual/Renderable.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/static/StaticImage.hpp>
#include <common/FVec2D.hpp>
#include <common/Cast.hpp>
#include <common/Error.hpp>

namespace mad::core {

    class RenderableStatic : public Renderable {
    public:
        explicit RenderableStatic(const std::shared_ptr<StaticImage>& static_image, std::shared_ptr<Vec2d> position,
                                  std::shared_ptr<float> rotation);

        bool render(sf::RenderWindow &window) override;

        sf::RectangleShape get_physical_shape() noexcept override;

    private:
        sf::Texture m_texture;

        Vec2d m_scale = {1, 1};

        std::optional<sf::IntRect> m_rect;

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

        sf::RectangleShape m_physical_shape;

    };

}

#endif //MAD_RENDERABLESTATIC_HPP
