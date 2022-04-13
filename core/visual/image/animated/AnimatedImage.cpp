#include "AnimatedImage.hpp"

#include <utility>

namespace mad::core {

    AnimatedImage::AnimatedImage(std::filesystem::path path, int height, int width, int count, sf::Time delta_time) :
                                Image(Image::Type::Animated), m_path(std::move(path)),
                                m_height(height), m_width(width), m_delta_time(delta_time) {

    }

}