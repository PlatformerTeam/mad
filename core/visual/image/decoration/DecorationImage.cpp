#include "DecorationImage.hpp"

#include <utility>
#include <iostream>

namespace mad::core {


    DecorationImage::DecorationImage(std::filesystem::path path, float scale, float delta_x, float delta_y)
                                    : Image(Image::Type::Decoration), m_path(std::move(path)), m_scale(scale),
                                    m_delta_x(delta_x), m_delta_y(delta_y) {
        std::cout << m_path << '\n';
    }

    std::filesystem::path DecorationImage::get_path() const noexcept {
        return m_path;
    }

    float DecorationImage::get_scale() const noexcept {
        return m_scale;
    }

    float DecorationImage::get_delta_x() const noexcept {
        return m_delta_x;
    }

    float DecorationImage::get_delta_y() const noexcept {
        return m_delta_y;
    }

    b2PolygonShape DecorationImage::as_fixture() {
        return {};
    }
}