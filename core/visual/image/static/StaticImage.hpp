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

        explicit StaticImage(std::filesystem::path path, float width, float height, TransformType transform_type);

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] float get_height() const noexcept;

        [[nodiscard]] float get_width() const noexcept;

        [[nodiscard]] TransformType get_transform_type() const noexcept;

    private:
        std::filesystem::path m_path;

        float m_height;

        float m_width;

        TransformType m_transform_type;
    };

}

#endif //MAD_STATICIMAGE_HPP
