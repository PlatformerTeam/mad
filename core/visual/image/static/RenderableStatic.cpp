#include "RenderableStatic.hpp"

#include <utility>

namespace mad::core {

    RenderableStatic::RenderableStatic(const std::shared_ptr<StaticImage>& static_image,
                                       std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation)
                                       : m_position(std::move(position)), m_rotation(std::move(rotation)) {

        is_active = static_image->is_active;
        is_reflect = static_image->is_reflect;

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

        if (*is_reflect && m_scale.get_x() > 0 || !*is_reflect && m_scale.get_x() < 0) {
            m_scale = {(-1) * m_scale.get_x(), m_scale.get_y()};
        }

        render_sprite.setScale(m_scale);

        if (m_rect) {
            render_sprite.setTextureRect(m_rect.value());
        }

        render_sprite.setOrigin(render_sprite.getLocalBounds().width / 2,
                                render_sprite.getLocalBounds().height / 2);

        render_sprite.setPosition(m_position->get_x(), m_position->get_y());

        render_sprite.setRotation(*m_rotation);

        window.draw(render_sprite);
    }

}

