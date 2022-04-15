#ifndef MAD_ANIMATEDIMAGE_HPP
#define MAD_ANIMATEDIMAGE_HPP

#include <visual/image/Image.hpp>

#include <SFML/Graphics.hpp>

#include <filesystem>

namespace mad::core {

    class AnimatedImage : public Image {
    public:
        explicit AnimatedImage(std::filesystem::path path, int width, int height, sf::Time delta_time);

        [[nodiscard]] sf::Time get_delta_time() const noexcept;

    private:
        sf::Time m_delta_time;

        std::filesystem::path m_path;

        int m_width;

        int m_height;
    };

}

#endif //MAD_ANIMATEDIMAGE_HPP
