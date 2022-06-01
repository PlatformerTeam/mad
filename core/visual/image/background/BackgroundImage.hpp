#ifndef MAD_BACKGROUNDIMAGE_HPP
#define MAD_BACKGROUNDIMAGE_HPP

#include <visual/image/Image.hpp>

#include <filesystem>
#include <vector>

namespace mad::core {

    class BackgroundImage : public Image {
    public:
        BackgroundImage(std::filesystem::path path, std::vector<float>  parallax_ratios, float scale);

        [[nodiscard]] std::filesystem::path get_path() const noexcept;

        [[nodiscard]] std::vector<float> get_parallax_ratios() const noexcept;

        [[nodiscard]] float get_scale() const noexcept;

        b2PolygonShape as_fixture() override;
    private:
        std::filesystem::path m_path;

        std::vector<float> m_parallax_ratios;

        float m_scale;
    };

}

#endif //MAD_BACKGROUNDIMAGE_HPP
