#include "RenderableAnimatedOneFile.hpp"

#include <utility>

namespace mad::core {

    RenderableAnimatedOneFile::RenderableAnimatedOneFile(const std::shared_ptr<AnimatedImageOneFile> &animated_image,
                                                         std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation)
    : m_delta_time(animated_image->get_delta_time()),
      m_position(std::move(position)), m_rotation(std::move(rotation)),
      m_delta_x(animated_image->get_delta_x()), m_delta_y(animated_image->get_delta_y()) {

        is_active = animated_image->is_active;
        m_orientation = animated_image->m_orientation;

        CHECK_THROW(m_texture.loadFromFile(
                            animated_image->get_path()),
                    FileDoesNotExist, "File with StaticImage doesn't exist");

        m_height_sprite = static_cast<int>(m_texture.getSize().y + 1) / animated_image->get_height();
        m_width_sprite = static_cast<int>(m_texture.getSize().x + 1) / animated_image->get_width();

        m_rect = {0, 0, m_width_sprite, m_height_sprite};

        m_scale = {animated_image->get_size_scale(), animated_image->get_size_scale()};

        float outline = 1;
        m_physical_shape = sf::RectangleShape({animated_image->get_physical_width() - outline,
                                               animated_image->get_physical_height() - outline});
        m_physical_shape.setOrigin((animated_image->get_physical_width() - outline) / 2,
                                   (animated_image->get_physical_height() - outline) / 2);
        m_physical_shape.setOutlineThickness(outline);
        m_physical_shape.setOutlineColor({0, 255, 0});
        m_physical_shape.setFillColor(sf::Color::Transparent);
    }

    bool RenderableAnimatedOneFile::render(sf::RenderWindow &window){
        bool is_render_all = false;

        sf::Sprite render_sprite;
        render_sprite.setTexture(m_texture);

        if (*m_orientation == Image::Orientation::Left && m_scale.get_x() > 0 ||
            *m_orientation == Image::Orientation::Right && m_scale.get_x() < 0) {
            m_scale = {(-1) * m_scale.get_x(), m_scale.get_y()};
        }

        render_sprite.setScale(m_scale);

        render_sprite.setTextureRect(m_rect);

        if (m_clock.getElapsedTime().asMilliseconds() >= m_delta_time) {
            update_frame(is_render_all);
            m_clock.restart();
        }

        render_sprite.setOrigin(render_sprite.getLocalBounds().width / 2,
                                render_sprite.getLocalBounds().height / 2);

        render_sprite.setPosition(m_position->get_x(), m_position->get_y());

        render_sprite.setRotation(*m_rotation);

        window.draw(render_sprite);

        return is_render_all;
    }

    void RenderableAnimatedOneFile::update_frame(bool &is_render_all) const {
        if (m_rect.left + m_width_sprite >= m_texture.getSize().x) {
            m_rect.left = 0;
            if (m_rect.top + m_height_sprite >= m_texture.getSize().y) {
                m_rect.top = 0;
            } else {
                m_rect.top += m_height_sprite;
                is_render_all = true;
            }
        } else {
            m_rect.left += m_width_sprite;
        }
    }

    sf::RectangleShape RenderableAnimatedOneFile::get_physical_shape() noexcept {
        m_physical_shape.setPosition(*m_position);
        m_physical_shape.setRotation(*m_rotation);
        return m_physical_shape;
    }
}