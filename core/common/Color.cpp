#include "Color.hpp"

namespace mad::core {

    Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue) : m_red(red), m_green(green), m_blue(blue) {
    }

    Color Color::Blue() {
        return {0, 0, 255};
    }

    Color Color::Green() {
        return {0, 255, 0};
    }

    Color Color::Red() {
        return {255, 0, 0};
    }

    Color Color::Black() {
        return {255, 255, 255};
    }

    Color Color::White() {
        return {0, 0, 0};
    }

}