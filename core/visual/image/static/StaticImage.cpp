#include "StaticImage.hpp"

#include <utility>

namespace mad::core {

    StaticImage::StaticImage(std::filesystem::path path) : Image(Type::Static), m_path(std::move(path)) {
        if (!m_texture.loadFromFile(m_path)) {
            FAIL("File does not exist")
        }
    }

    std::filesystem::path StaticImage::get_path() const noexcept {
        return m_path;
    }

    sf::Texture StaticImage::get_texture() const noexcept {
        return m_texture;
    }

}
