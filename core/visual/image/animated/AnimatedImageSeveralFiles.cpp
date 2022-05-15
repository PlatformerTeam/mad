#include "AnimatedImageSeveralFiles.hpp"

namespace mad::core {

    AnimatedImageSeveralFiles::AnimatedImageSeveralFiles(std::filesystem::path path, int32_t delta_time,
                                                         float sprite_width, float sprite_height,
                                                         float width_scale, float height_scale) :
            Image(Image::Type::AnimatedSeveralFiles), m_path(std::move(path)), m_delta_time(delta_time),
            m_sprite_width(sprite_width), m_sprite_height(sprite_height),
            m_width_scale(width_scale), m_height_scale(height_scale) {
    }

    int32_t AnimatedImageSeveralFiles::get_delta_time() const noexcept {
        return m_delta_time;
    }

    std::filesystem::path AnimatedImageSeveralFiles::get_path() const noexcept {
        return m_path;
    }

    b2PolygonShape AnimatedImageSeveralFiles::as_fixture() {
        b2PolygonShape fixture;
        fixture.SetAsBox(m_sprite_width / 2, m_sprite_height / 2);
        return fixture;
    }

    float AnimatedImageSeveralFiles::get_sprite_height() const noexcept {
        return m_sprite_height;
    }

    float AnimatedImageSeveralFiles::get_sprite_width() const noexcept {
        return m_sprite_width;
    }

    float AnimatedImageSeveralFiles::get_width_scale() const noexcept {
        return m_width_scale;
    }

    float AnimatedImageSeveralFiles::get_height_scale() const noexcept {
        return m_height_scale;
    }

}
