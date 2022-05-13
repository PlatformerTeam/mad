#include "RenderableAnimatedOneFile.hpp"

#include <utility>

namespace mad::core {

    RenderableAnimatedOneFile::RenderableAnimatedOneFile(const std::shared_ptr<AnimatedImageOneFile> &animated_image,
                                                         std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation)
    : m_delta_time(animated_image->get_delta_time()),
      m_position(std::move(position)), m_rotation(std::move(rotation)),
      m_width_scale(animated_image->get_width_scale()),
      m_height_scale(animated_image->get_height_scale()) {

        is_active = animated_image->is_active;

        CHECK_THROW(m_texture.loadFromFile(
                            animated_image->get_path()),
                    FileDoesNotExist, "File with StaticImage doesn't exist");

        m_height_sprite = static_cast<int>(m_texture.getSize().y + 1) / animated_image->get_height();
        m_width_sprite = static_cast<int>(m_texture.getSize().x + 1) / animated_image->get_width();

        m_rect = {0, 0, m_width_sprite, m_height_sprite};

        m_scale = {animated_image->get_sprite_width() / static_cast<float>(m_width_sprite) * m_width_scale,
                   animated_image->get_sprite_height() / static_cast<float>(m_height_sprite) * m_height_scale};
    }

    void RenderableAnimatedOneFile::render(sf::RenderWindow &window){
        sf::Sprite render_sprite;
        render_sprite.setTexture(m_texture);

        render_sprite.setScale(m_scale);

        render_sprite.setTextureRect(m_rect);

        if (m_clock.getElapsedTime().asMilliseconds() >= m_delta_time) {
            update_frame();
            m_clock.restart();
        }

        render_sprite.setOrigin(render_sprite.getLocalBounds().width / 2,
                                render_sprite.getLocalBounds().height / 2);

        render_sprite.setPosition(m_position->get_x(), m_position->get_y());

        render_sprite.setRotation(*m_rotation);

        window.draw(render_sprite);
    }

    void RenderableAnimatedOneFile::update_frame() const {
        if (m_rect.left + m_width_sprite >= m_texture.getSize().x) {
            m_rect.left = 0;
            if (m_rect.top + m_height_sprite >= m_texture.getSize().y) {
                m_rect.top = 0;
            } else {
                m_rect.top += m_height_sprite;
            }
        } else {
            m_rect.left += m_width_sprite;
        }
    }

}