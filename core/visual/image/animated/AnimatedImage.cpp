#include "AnimatedImage.hpp"

#include <utility>

namespace mad::core {

    AnimatedImage::AnimatedImage(std::filesystem::path path, int width, int height, sf::Time delta_time) :
                                Image(Image::Type::Animated), m_path(std::move(path)),
                                m_width(width), m_height(height), m_delta_time(delta_time) {
    }

    sf::Time AnimatedImage::get_delta_time() const noexcept {
        return m_delta_time;
    }

}