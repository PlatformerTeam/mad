#include "AnimatedImage.hpp"

#include <utility>

namespace mad::core {

    AnimatedImage::AnimatedImage(std::filesystem::path path, int width, int height,
                                 int32_t delta_time, float width_size, float height_size) :
                                Image(Image::Type::Animated), m_path(std::move(path)),
                                m_width(width), m_height(height), m_delta_time(delta_time),
                                m_width_size(width_size), m_height_size(height_size) {
    }

    int32_t AnimatedImage::get_delta_time() const noexcept {
        return m_delta_time;
    }

    std::filesystem::path AnimatedImage::get_path() const noexcept {
        return m_path;
    }

    int AnimatedImage::get_width() const noexcept {
        return m_width;
    }

    int AnimatedImage::get_height() const noexcept {
        return m_height;
    }

    b2PolygonShape AnimatedImage::as_fixture() {
        b2PolygonShape fixture;
        fixture.SetAsBox((m_width_size / static_cast<float>(m_width)) / 2,
                         (m_height_size / static_cast<float>(m_height)) / 2);
        return fixture;
    }


}