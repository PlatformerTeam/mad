#include "RenderableAnimatedSeveralFiles.hpp"
#include "spdlog/spdlog.h"

#include <algorithm>
#include <set>
#include <utility>

namespace mad::core {

    RenderableAnimatedSeveralFiles::RenderableAnimatedSeveralFiles(const std::shared_ptr<AnimatedImageSeveralFiles> &animated_image,
                                                                   std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation)
            : m_delta_time(animated_image->get_delta_time()),
              m_position(std::move(position)), m_rotation(std::move(rotation)),
              m_delta_x(animated_image->get_delta_x()), m_delta_y(animated_image->get_delta_y()) {

        is_active = animated_image->is_active;
        m_orientation = animated_image->m_orientation;

        std::set<std::string> sorted_files;

        for (const auto &file : std::filesystem::directory_iterator{animated_image->get_path()}) {
            sorted_files.insert(file.path());
        }

        for (const auto &file_name : sorted_files) {
            sf::Texture texture;
            CHECK_THROW(texture.loadFromFile(file_name),
                        FileDoesNotExist, "File with StaticImage doesn't exist");
            m_textures.push_back(texture);
        }

        m_current_frame = m_textures.size();

        //std::reverse(m_textures.begin(), m_textures.end());

        auto [texture_width, texture_height] = m_textures[0].getSize();

        m_scale = {animated_image->get_size_scale(), animated_image->get_size_scale()};

        float outline = 0.2;
        m_physical_shape = sf::RectangleShape({animated_image->get_physical_width() - outline,
                                              animated_image->get_physical_height() - outline});
        m_physical_shape.setOrigin((animated_image->get_physical_width() - outline) / 2,
                                   (animated_image->get_physical_height() - outline) / 2);
        m_physical_shape.setOutlineThickness(outline);
        m_physical_shape.setOutlineColor({0, 255, 0});
        m_physical_shape.setFillColor(sf::Color::Transparent);
    }

    bool RenderableAnimatedSeveralFiles::render(sf::RenderWindow &window){
        bool is_render_all = false;

        if (m_current_frame == m_textures.size()) {
            m_current_frame = 0;
            m_clock.restart();
        }

        sf::Sprite render_sprite;
        if(m_current_frame != debug_prev_sprite_num){
            debug_prev_sprite_num = m_current_frame;
            SPDLOG_DEBUG("current frame number {}", m_current_frame);
        }
        render_sprite.setTexture(m_textures[m_current_frame]);

        if (*m_orientation == Image::Orientation::Left && m_scale.get_x() > 0 ||
            *m_orientation == Image::Orientation::Right && m_scale.get_x() < 0) {
            m_scale = {(-1) * m_scale.get_x(), m_scale.get_y()};
        }

        render_sprite.setScale(m_scale);

        render_sprite.setOrigin(render_sprite.getLocalBounds().width / 2 + m_delta_x,
                                render_sprite.getLocalBounds().height / 2 + m_delta_y);

        render_sprite.setPosition(m_position->get_x(), m_position->get_y());

        render_sprite.setRotation(*m_rotation);

        window.draw(render_sprite);

        if (m_clock.getElapsedTime().asMilliseconds() >= m_delta_time) {
            update_frame();
            m_clock.restart();
        }

        if (m_current_frame == m_textures.size()) {
            is_render_all = true;
        }

        return is_render_all;
    }

    void RenderableAnimatedSeveralFiles::update_frame() {
        m_current_frame += 1;
    }

    sf::RectangleShape RenderableAnimatedSeveralFiles::get_physical_shape() noexcept {
        m_physical_shape.setPosition(*m_position);
        m_physical_shape.setRotation(*m_rotation);
        return m_physical_shape;
    }

}

