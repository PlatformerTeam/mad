#include "RenderableAnimatedSeveralFiles.hpp"

#include <utility>
#include <algorithm>

namespace mad::core {

    RenderableAnimatedSeveralFiles::RenderableAnimatedSeveralFiles(const std::shared_ptr<AnimatedImageSeveralFiles> &animated_image,
                                                         std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation)
            : m_delta_time(animated_image->get_delta_time()),
              m_position(std::move(position)), m_rotation(std::move(rotation)),
              m_width_scale(animated_image->get_width_scale()),
              m_height_scale(animated_image->get_height_scale()) {

        is_active = animated_image->is_active;
        m_orientation = animated_image->m_orientation;

        for (const auto &file : std::filesystem::directory_iterator{animated_image->get_path()}) {
            sf::Texture texture;
            CHECK_THROW(texture.loadFromFile(file.path()),
                    FileDoesNotExist, "File with StaticImage doesn't exist");
            m_textures.push_back(texture);
        }

        std::reverse(m_textures.begin(), m_textures.end());

        auto [texture_width, texture_height] = m_textures[0].getSize();

        m_scale = {animated_image->get_sprite_width() / static_cast<float>(texture_width) * m_width_scale,
                   animated_image->get_sprite_height() / static_cast<float>(texture_height) * m_height_scale};
    }

    void RenderableAnimatedSeveralFiles::render(sf::RenderWindow &window){
        if (m_clock.getElapsedTime().asMilliseconds() >= m_delta_time) {
            update_frame();
            m_clock.restart();
        }

        sf::Sprite render_sprite;
        render_sprite.setTexture(m_textures[m_current_frame]);

        if (*m_orientation == Image::Orientation::Left && m_scale.get_x() > 0 ||
            *m_orientation == Image::Orientation::Right && m_scale.get_x() < 0) {
            m_scale = {(-1) * m_scale.get_x(), m_scale.get_y()};
        }

        render_sprite.setScale(m_scale);

        render_sprite.setOrigin(render_sprite.getLocalBounds().width / 2,
                                render_sprite.getLocalBounds().height / 2);

        render_sprite.setPosition(m_position->get_x(), m_position->get_y());

        render_sprite.setRotation(*m_rotation);

        window.draw(render_sprite);
    }

    void RenderableAnimatedSeveralFiles::update_frame() {
        m_current_frame += 1;
        if (m_current_frame == m_textures.size()) {
            m_current_frame = 0;
        }
    }

}

