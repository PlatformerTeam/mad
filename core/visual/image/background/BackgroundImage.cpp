#include "BackgroundImage.hpp"

#include <utility>

namespace mad::core {


    BackgroundImage::BackgroundImage(std::filesystem::path path, float parallax_ratio)
                                    : Image(Image::Type::Background), m_path(std::move(path)),
                                    m_parallax_ratio(parallax_ratio) {
    }

    std::filesystem::path BackgroundImage::get_path() const noexcept {
        return m_path;
    }

    float BackgroundImage::get_parallax_ratio() const noexcept {
        return m_parallax_ratio;
    }

    b2PolygonShape BackgroundImage::as_fixture() {
        return {};
    }


}

