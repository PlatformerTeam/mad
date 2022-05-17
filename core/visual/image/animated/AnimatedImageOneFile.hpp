#ifndef MAD_ANIMATEDIMAGEONEFILE_HPP
#define MAD_ANIMATEDIMAGEONEFILE_HPP

#include <visual/image/Image.hpp>

#include <SFML/Graphics.hpp>

#include <filesystem>

namespace mad::core {

    class AnimatedImageOneFile : public Image {
    public:
        explicit AnimatedImageOneFile(std::filesystem::path path, int width, int height, int32_t delta_time,
                                      float physical_width, float physical_height, float size_scale, float delta_x,
                                      float delta_y);

        [[nodiscard]] int32_t get_delta_time() const noexcept;

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] int get_width() const noexcept;

        [[nodiscard]] int get_height() const noexcept;

        [[nodiscard]] float get_physical_height() const noexcept;

        [[nodiscard]] float get_physical_width() const noexcept;

        [[nodiscard]] float get_delta_x() const noexcept;

        [[nodiscard]] float get_delta_y() const noexcept;

        b2PolygonShape as_fixture() override;

        [[nodiscard]] float get_size_scale() const noexcept;

    private:
        int32_t m_delta_time;

        std::filesystem::path m_path;

        int m_width;

        int m_height;

        float m_physical_height;

        float m_physical_width;

        float m_size_scale;

        float m_delta_x;

        float m_delta_y;
    };

}

#endif //MAD_ANIMATEDIMAGEONEFILE_HPP
