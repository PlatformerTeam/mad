#include "StaticImage.hpp"

#include <utility>

namespace mad::core {

    StaticImage::StaticImage(std::filesystem::path path, float width, float height, TransformType transform_type) :
                        Image(Type::Static), m_path(std::move(path)), m_height(height),
                        m_width(width), m_transform_type(transform_type) {
    }

    std::filesystem::path StaticImage::get_path() const noexcept {
        return m_path;
    }

    float StaticImage::get_height() const noexcept {
        return m_height;
    }

    float StaticImage::get_width() const noexcept {
        return m_width;
    }

    StaticImage::TransformType StaticImage::get_transform_type() const noexcept {
        return m_transform_type;
    }

}
