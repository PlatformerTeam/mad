#ifndef MAD_CORE_COMMON_COLOR_HPP
#define MAD_CORE_COMMON_COLOR_HPP

#include <cstdint>


namespace mad::core {

    class Color {
    public:
        Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue) : m_red(red), m_green(green), m_blue(blue) {
        }

    private:
        std::uint8_t m_red, m_green, m_blue;
    };

}

#endif //MAD_CORE_COMMON_COLOR_HPP
