#ifndef MAD_RENDERABLEIMAGE_HPP
#define MAD_RENDERABLEIMAGE_HPP

#include <visual/Renderable.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/shape/Shape.hpp>
#include <visual/image/shape/Square.hpp>
#include <visual/image/static/StaticImage.hpp>
#include <common/FVec2D.hpp>
#include <common/Cast.hpp>
#include <common/Error.hpp>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include <filesystem>

namespace mad::core {

    class RenderableImage : public Renderable {

        struct RenderableStatic {
            StaticImage::TransformType m_transform_type;

            std::filesystem::path m_path;

            sf::Texture m_texture;

            Vec2d m_scale = {1, 1};

            std::optional<sf::IntRect> m_rect;

            float m_width;

            float m_height;
        };

        struct RenderableAnimated {

        };

    public:
        explicit RenderableImage(const std::shared_ptr<Image>& image,
                                 std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation);

        void render(sf::RenderWindow &window) override;

        void render_shape(sf::RenderWindow &window);

        void render_static(sf::RenderWindow &window);

        void render_animated(sf::RenderWindow &window);

    private:
        Image::Type type;

        RenderableStatic m_renderable_static;

        std::shared_ptr<Shape> m_shape;

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;
    };

}

#endif //MAD_RENDERABLEIMAGE_HPP
