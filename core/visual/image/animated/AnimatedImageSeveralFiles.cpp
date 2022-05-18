#include "AnimatedImageSeveralFiles.hpp"

namespace mad::core {

    AnimatedImageSeveralFiles::AnimatedImageSeveralFiles(std::filesystem::path path, int32_t delta_time,
                                                         float physical_width, float physical_height, float size_scale,
                                                         float delta_x, float delta_y) :
            Image(Image::Type::AnimatedSeveralFiles), m_path(std::move(path)), m_delta_time(delta_time),
            m_physical_width(physical_width), m_physical_height(physical_height), m_size_scale(size_scale),
            m_delta_x(delta_x), m_delta_y(delta_y) {
    }

    int32_t AnimatedImageSeveralFiles::get_delta_time() const noexcept {
        return m_delta_time;
    }

    std::filesystem::path AnimatedImageSeveralFiles::get_path() const noexcept {
        return m_path;
    }

    b2PolygonShape AnimatedImageSeveralFiles::as_fixture() {
        b2PolygonShape fixture;
        fixture.SetAsBox(m_physical_width / 2, m_physical_height / 2);
        return fixture;
    }

    float AnimatedImageSeveralFiles::get_physical_height() const noexcept {
        return m_physical_height;
    }

    float AnimatedImageSeveralFiles::get_physical_width() const noexcept {
        return m_physical_width;
    }

    float AnimatedImageSeveralFiles::get_size_scale() const noexcept {
        return m_size_scale;
    }

    float AnimatedImageSeveralFiles::get_delta_x() const noexcept {
        return m_delta_x;
    }

    float AnimatedImageSeveralFiles::get_delta_y() const noexcept {
        return m_delta_y;
    }

}
