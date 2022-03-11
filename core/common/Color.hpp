#ifndef MAD_CORE_COMMON_COLOR_HPP
#define MAD_CORE_COMMON_COLOR_HPP

#include <cstdint>


namespace mad::core {

    class Color {
    public:
        Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue);

        [[nodiscard]] std::uint8_t get_red() const;

        [[nodiscard]] std::uint8_t get_green() const;

        [[nodiscard]] std::uint8_t get_blue() const;

        static Color Blue();

        static Color Green();

        static Color Red();

        static Color Black();

        static Color White();

    private:
        std::uint8_t m_red, m_green, m_blue;
    };

}

#endif //MAD_CORE_COMMON_COLOR_HPP
