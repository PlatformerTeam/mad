#include "RenderableStatic.hpp"

#include <utility>

namespace mad::core {

    RenderableStatic::RenderableStatic(const std::shared_ptr<StaticImage>& static_image,
                                       std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation)
                                       : m_position(std::move(position)), m_rotation(std::move(rotation)),
                                         m_unique_number(static_image->get_unique_number()) {

        CHECK_THROW(m_texture.loadFromFile(
                static_image->get_path()),
                    FileDoesNotExist, "File with StaticImage doesn't exist");

        switch (static_image->get_transform_type()) {

            case StaticImage::TransformType::Fit: {
                auto[texture_width, texture_height] = m_texture.getSize();
                m_scale = {static_image->get_width() / static_cast<float>(texture_width),
                           static_image->get_height() / static_cast<float>(texture_height)};
                break;
            }

            case StaticImage::TransformType::Tile: {
                m_texture.setRepeated(true);
                m_rect = {0, 0, static_cast<int>(static_image->get_width()),
                                              static_cast<int>(static_image->get_height())};
                break;
            }
        }
    }

    void RenderableStatic::render(sf::RenderWindow &window) {
        sf::Sprite render_sprite;

        render_sprite.setTexture(m_texture);

        render_sprite.setScale(m_scale.get_x(), m_scale.get_y());

        if (m_rect) {
            render_sprite.setTextureRect(m_rect.value());
        }

        render_sprite.setOrigin(render_sprite.getLocalBounds().width / 2,
                                render_sprite.getLocalBounds().height / 2);

        render_sprite.setPosition(m_position->get_x(), m_position->get_y());

        render_sprite.setRotation(*m_rotation * 180 / M_PI);

        window.draw(render_sprite);
    }

    int RenderableStatic::get_unique_number() const noexcept {
        return m_unique_number;
    }

}

