#ifndef MAD_RENDERABLESQUARE_HPP
#define MAD_RENDERABLESQUARE_HPP

#include <visual/Renderable.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/shape/square/Square.hpp>
#include <common/FVec2D.hpp>
#include <common/Cast.hpp>
#include <common/Error.hpp>

#include <SFML/Graphics.hpp>

namespace mad::core {

    class RenderableSquare : public Renderable {
    public:
        RenderableSquare(std::shared_ptr<Square> shape, std::shared_ptr<Vec2d> position,
                         std::shared_ptr<float> rotation);

        bool render(sf::RenderWindow &window) override;

        sf::RectangleShape get_physical_shape() noexcept override;

    private:
        std::shared_ptr<Shape> m_shape;

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

        sf::RectangleShape m_physical_shape;
    };

}

#endif //MAD_RENDERABLESQUARE_HPP
