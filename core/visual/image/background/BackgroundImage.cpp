#include "BackgroundImage.hpp"

#include <utility>

namespace mad::core {


    BackgroundImage::BackgroundImage(std::filesystem::path path, std::vector<float>  parallax_ratios, float scale)
                                    : Image(Image::Type::Background), m_path(std::move(path)),
                                    m_parallax_ratios(std::move(parallax_ratios)), m_scale(scale) {
    }

    std::filesystem::path BackgroundImage::get_path() const noexcept {
        return m_path;
    }

    std::vector<float> BackgroundImage::get_parallax_ratios() const noexcept {
        return m_parallax_ratios;
    }

    b2PolygonShape BackgroundImage::as_fixture() {
        return {};
    }

    float BackgroundImage::get_scale() const noexcept {
        return m_scale;
    }


}

