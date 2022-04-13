#ifndef MAD_ANIMATEDIMAGE_HPP
#define MAD_ANIMATEDIMAGE_HPP

#include <visual/image/Image.hpp>

#include <SFML/Graphics.hpp>

#include <filesystem>

namespace mad::core {

    class AnimatedImage : public Image {
    public:
        explicit AnimatedImage(std::filesystem::path path, int height, int width, int count, sf::Time delta_time);

    private:
        sf::Time m_delta_time;

        std::filesystem::path m_path;

        int m_height;

        int m_width;

        int m_count_rows;
    };

}

#endif //MAD_ANIMATEDIMAGE_HPP
