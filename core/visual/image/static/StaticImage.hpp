#ifndef MAD_STATICIMAGE_HPP
#define MAD_STATICIMAGE_HPP

#include <visual/image/Image.hpp>
#include <common/Error.hpp>

#include <SFML/Graphics.hpp>

#include <filesystem>

namespace mad::core {

    class StaticImage : public Image {
    public:
        explicit StaticImage(std::filesystem::path path);

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] sf::Texture get_texture() const noexcept;

    private:
        std::filesystem::path m_path;

        sf::Texture m_texture;
    };

}

#endif //MAD_STATICIMAGE_HPP
