#include "StaticImage.hpp"
#include <common/Error.hpp>

#include <utility>

namespace mad::core {

    StaticImage::StaticImage(std::filesystem::path path, Vec2d scale, std::optional<sf::IntRect> rect) :
                        Image(Type::Static), m_path(std::move(path)),
                        m_scale(scale), m_rect(rect) {
        CHECK_THROW(m_texture.loadFromFile(m_path), FileDoesNotExist, "File with StaticImage doesn't exist");
    }

    std::filesystem::path StaticImage::get_path() const noexcept {
        return m_path;
    }

    sf::Texture StaticImage::get_texture() const noexcept {
        return m_texture;
    }

    Vec2d StaticImage::get_scale() const noexcept {
        return m_scale;
    }

    std::optional<sf::IntRect> StaticImage::get_rect() const noexcept {
        return m_rect;
    }

    void StaticImage::set_scale(const Vec2d &scale) {
        m_scale = scale;
    }

    void StaticImage::set_rect(sf::IntRect rect) {
        m_rect = rect;
    }

    void StaticImage::set_shape(int width, int height, StaticImage::TransformType transform_type) {
        CHECK_THROW(width > 0, InvalidArgument, "Negative width");
        CHECK_THROW(height > 0, InvalidArgument, "Negative height");

        switch (transform_type) {

            case TransformType::Fit: {
                auto[texture_width, texture_height] = m_texture.getSize();
                m_scale = {static_cast<float>(width) / static_cast<float>(texture_width),
                           static_cast<float>(height) / static_cast<float>(texture_height)};
                break;
            }

            case TransformType::Tile: {
                m_texture.setRepeated(true);
                m_rect = {0, 0, width,height};
                break;
            }
        }
    }

}
