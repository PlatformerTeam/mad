#include "AnimatedImageOneFile.hpp"

#include <utility>

namespace mad::core {

    AnimatedImageOneFile::AnimatedImageOneFile(std::filesystem::path path, int width, int height,
                                               int32_t delta_time, float physical_width, float physical_height,
                                               float size_scale, float delta_x, float delta_y) :
                                Image(Image::Type::AnimatedOneFile), m_path(std::move(path)),
                                m_width(width), m_height(height), m_delta_time(delta_time),
                                m_physical_width(physical_width), m_physical_height(physical_height),
                                m_size_scale(size_scale), m_delta_x(delta_x), m_delta_y(delta_y) {
    }

    int32_t AnimatedImageOneFile::get_delta_time() const noexcept {
        return m_delta_time;
    }

    std::filesystem::path AnimatedImageOneFile::get_path() const noexcept {
        return m_path;
    }

    int AnimatedImageOneFile::get_width() const noexcept {
        return m_width;
    }

    int AnimatedImageOneFile::get_height() const noexcept {
        return m_height;
    }

    b2PolygonShape AnimatedImageOneFile::as_fixture() {
        b2PolygonShape fixture;
        fixture.SetAsBox(m_physical_width / 2, m_physical_height / 2);
        return fixture;
    }

    float AnimatedImageOneFile::get_physical_height() const noexcept {
        return m_physical_height;
    }

    float AnimatedImageOneFile::get_physical_width() const noexcept {
        return m_physical_width;
    }

    float AnimatedImageOneFile::get_size_scale() const noexcept {
        return m_size_scale;
    }

    float AnimatedImageOneFile::get_delta_x() const noexcept {
        return m_delta_x;
    }

    float AnimatedImageOneFile::get_delta_y() const noexcept {
        return m_delta_y;
    }

}