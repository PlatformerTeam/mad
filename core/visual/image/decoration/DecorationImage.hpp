#ifndef MAD_DECORATIONIMAGE_HPP
#define MAD_DECORATIONIMAGE_HPP

#include <visual/image/Image.hpp>

#include <filesystem>

namespace mad::core {

    class DecorationImage : public Image {
    public:
        explicit DecorationImage(std::filesystem::path path, float scale, float delta_x, float delta_y);

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] float get_scale() const noexcept;

        [[nodiscard]] float get_delta_x() const noexcept;

        [[nodiscard]] float get_delta_y() const noexcept;

        [[nodiscard]] b2PolygonShape as_fixture() override;

    private:
        std::filesystem::path m_path;

        float m_scale;

        float m_delta_x;

        float m_delta_y;
    };

}



#endif //MAD_DECORATIONIMAGE_HPP
