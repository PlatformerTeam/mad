#include "RenderableDecoration.hpp"

namespace mad::core {


    RenderableDecoration::RenderableDecoration(const std::shared_ptr<DecorationImage> &decoration_image,
                                               std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation)
                                               : m_position(std::move(position)), m_rotation(std::move(rotation)),
                                               m_delta_x(decoration_image->get_delta_x()), m_delta_y(decoration_image->get_delta_y()) {

        is_active = decoration_image->is_active;
        m_orientation = decoration_image->m_orientation;

        m_scale = {decoration_image->get_scale(), decoration_image->get_scale()};

        CHECK_THROW(m_texture.loadFromFile(
                    decoration_image->get_path()),
                    FileDoesNotExist, "File with DecorateImage doesn't exist");

    }

    bool RenderableDecoration::render(sf::RenderWindow &window) {
        sf::Sprite render_sprite;

        render_sprite.setTexture(m_texture);

        render_sprite.setScale(m_scale);

        render_sprite.setOrigin(render_sprite.getLocalBounds().width / 2 + m_delta_x,
                                render_sprite.getLocalBounds().height / 2 + m_delta_y);

        render_sprite.setPosition(m_position->get_x(), m_position->get_y());

        render_sprite.setRotation(*m_rotation);

        window.draw(render_sprite);

        return true;
    }

    sf::RectangleShape RenderableDecoration::get_physical_shape() noexcept {
        return sf::RectangleShape();
    }
}

