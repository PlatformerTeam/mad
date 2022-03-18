#ifndef MAD_STATICIMAGE_HPP
#define MAD_STATICIMAGE_HPP

#include <visual/image/Image.hpp>
#include <common/FVec2D.hpp>

#include <SFML/Graphics.hpp>

#include <filesystem>

namespace mad::core {

    class StaticImage : public Image {
    public:
        enum class TransformType {
            Fit,
            Tile
        };

        explicit StaticImage(std::filesystem::path path, Vec2d scale = {1.0, 1.0},
                             std::optional<sf::IntRect> rect = std::nullopt);

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] sf::Texture get_texture() const noexcept;

        [[nodiscard]] Vec2d get_scale() const noexcept;

        [[nodiscard]] std::optional<sf::IntRect> get_rect() const noexcept;

        void set_scale(const Vec2d &scale);

        void set_rect(sf::IntRect rect);

        void set_shape(std::uint32_t width, std::uint32_t height, TransformType transform_type);

    private:
        std::filesystem::path m_path;

        sf::Texture m_texture;

        Vec2d m_scale;

        std::optional<sf::IntRect> m_rect;
    };

}

#endif //MAD_STATICIMAGE_HPP
