#ifndef MAD_BACKGROUNDIMAGE_HPP
#define MAD_BACKGROUNDIMAGE_HPP

#include <visual/image/Image.hpp>

#include <filesystem>

namespace mad::core {

    class BackgroundImage : public Image {
    public:
        BackgroundImage(std::filesystem::path path, float parallax_ratio);

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] float get_parallax_ratio() const noexcept;

        b2PolygonShape as_fixture() override;
    private:
        std::filesystem::path m_path;

        float m_parallax_ratio;
    };

}

#endif //MAD_BACKGROUNDIMAGE_HPP
