#include "AnimatedImageSeveralFiles.hpp"

namespace mad::core {

    AnimatedImageSeveralFiles::AnimatedImageSeveralFiles(std::filesystem::path path, int count_sprites,
                                                         int32_t delta_time, float sprite_width, float sprite_height) :
            Image(Image::Type::AnimatedSeveralFiles), m_path(std::move(path)),
            m_count_sprites(count_sprites), m_delta_time(delta_time),
            m_sprite_width(sprite_width), m_sprite_height(sprite_height) {
    }

    int32_t AnimatedImageSeveralFiles::get_delta_time() const noexcept {
        return m_delta_time;
    }

    std::filesystem::path AnimatedImageSeveralFiles::get_path() const noexcept {
        return m_path;
    }

    int AnimatedImageSeveralFiles::get_count_sprites() const noexcept {
        return m_count_sprites;
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

}
