#ifndef MAD_ANIMATEDIMAGESEVERALFILES_HPP
#define MAD_ANIMATEDIMAGESEVERALFILES_HPP

#include <visual/image/Image.hpp>

#include <SFML/Graphics.hpp>

#include <filesystem>

namespace mad::core {

    class AnimatedImageSeveralFiles : public Image {
    public:
        explicit AnimatedImageSeveralFiles(std::filesystem::path path, int32_t delta_time, float sprite_width,
                                           float sprite_height, float width_scale, float height_scale);

        [[nodiscard]] int32_t get_delta_time() const noexcept;

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] float get_sprite_height() const noexcept;

        [[nodiscard]] float get_sprite_width() const noexcept;

        b2PolygonShape as_fixture() override;

        [[nodiscard]] float get_width_scale() const noexcept;

        [[nodiscard]] float get_height_scale() const noexcept;

    private:
        int32_t m_delta_time;

        std::filesystem::path m_path;

        float m_sprite_height;

        float m_sprite_width;

        float m_width_scale;

        float m_height_scale;
    };

}

#endif //MAD_ANIMATEDIMAGESEVERALFILES_HPP
