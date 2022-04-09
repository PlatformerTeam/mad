#include "RenderableImage.hpp"

#include <utility>

namespace mad::core {

    RenderableImage::RenderableImage(const std::shared_ptr<Image>& image, std::shared_ptr<Vec2d> position,
                                     std::shared_ptr<float> rotation)
                                     : type(image->type), m_position(std::move(position)), m_rotation(std::move(rotation)),
                                     m_unique_number(image->get_unique_number()) {
        switch (type) {
            case Image::Type::Shape: {
                m_shape = pointer_cast_to<Shape>(image);
                break;
            }

            case Image::Type::Static: {
                auto static_image = pointer_cast_to<StaticImage>(image);
                m_renderable_static.m_path = static_image->get_path();
                m_renderable_static.m_height = static_image->get_height();
                m_renderable_static.m_width = static_image->get_width();
                m_renderable_static.m_transform_type = static_image->get_transform_type();

                CHECK_THROW(m_renderable_static.m_texture.loadFromFile(
                        m_renderable_static.m_path),
                            FileDoesNotExist, "File with StaticImage doesn't exist");

                switch (m_renderable_static.m_transform_type) {

                    case StaticImage::TransformType::Fit: {
                        auto[texture_width, texture_height] = m_renderable_static.m_texture.getSize();
                        m_renderable_static.m_scale = {m_renderable_static.m_width /
                                                              static_cast<float>(texture_width),
                                                              m_renderable_static.m_height /
                                                              static_cast<float>(texture_height)};
                        break;
                    }

                    case StaticImage::TransformType::Tile: {
                        m_renderable_static.m_texture.setRepeated(true);
                        m_renderable_static.m_rect = {0, 0, static_cast<int>(m_renderable_static.m_width),
                                                      static_cast<int>(m_renderable_static.m_height)};
                        break;
                    }
                }
                break;
            }

            case Image::Type::Animated: {

            }
        }
    }

    void RenderableImage::render(sf::RenderWindow &window) const {
        switch (type) {

            case Image::Type::Shape: {
                render_shape(window);
                break;
            }

            case Image::Type::Static: {
                render_static(window);
                break;
            }

            case Image::Type::Animated:
                break;
        }
    }

    void RenderableImage::render_shape(sf::RenderWindow &window) const {
        switch (m_shape->get_geometry()) {

            case Shape::Geometry::Square: {
                Square square = *pointer_cast_to<Square>(m_shape);
                sf::RectangleShape render_square({square.get_side_length(), square.get_side_length()});
                render_square.setOrigin(square.get_side_length() / 2, square.get_side_length() / 2);

                Color square_color = square.get_color();

                render_square.setFillColor({square_color.get_red(),
                                            square_color.get_green(),
                                            square_color.get_blue()});


                render_square.setPosition(m_position->get_x(), m_position->get_y());
                render_square.setRotation(*m_rotation);
                window.draw(render_square);
            }
        }
    }

    void RenderableImage::render_static(sf::RenderWindow &window) const {
        sf::Sprite render_sprite;

        render_sprite.setTexture(m_renderable_static.m_texture);

        render_sprite.setScale(m_renderable_static.m_scale.get_x(), m_renderable_static.m_scale.get_y());

        if (m_renderable_static.m_rect) {
            render_sprite.setTextureRect(m_renderable_static.m_rect.value());
        }

        render_sprite.setOrigin(render_sprite.getLocalBounds().width / 2,
                                render_sprite.getLocalBounds().height / 2);

        render_sprite.setPosition(m_position->get_x(), m_position->get_y());

        render_sprite.setRotation(*m_rotation * 180 / M_PI);

        window.draw(render_sprite);
    }

    void RenderableImage::render_animated(sf::RenderWindow &window) const {

    }

    int RenderableImage::get_unique_number() const noexcept {
        return m_unique_number;
    }


}