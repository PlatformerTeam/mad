#ifndef MAD_ANIMATEDIMAGE_HPP
#define MAD_ANIMATEDIMAGE_HPP

#include <visual/image/Image.hpp>

#include <SFML/Graphics.hpp>

#include <filesystem>

namespace mad::core {

    class AnimatedImage : public Image {
    public:
        explicit AnimatedImage(std::filesystem::path path, int width, int height, int32_t delta_time,
                               float sprite_width, float sprite_height);

        [[nodiscard]] int32_t get_delta_time() const noexcept;

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] int get_width() const noexcept;

        [[nodiscard]] int get_height() const noexcept;

        [[nodiscard]] float get_sprite_height() const noexcept;

        [[nodiscard]] float get_sprite_width() const noexcept;

        b2PolygonShape as_fixture() override;

    private:
        int32_t m_delta_time;

        std::filesystem::path m_path;

        int m_width;

        int m_height;

        float m_sprite_height;

        float m_sprite_width;
    };

}

#endif //MAD_ANIMATEDIMAGE_HPP
