#ifndef MAD_SQUARE_HPP
#define MAD_SQUARE_HPP

#include "Shape.hpp"

namespace mad::core {

    struct Square : Shape {
    public:
        explicit Square(std::uint32_t side, Color color);

        [[nodiscard]] std::uint32_t get_side_length() const noexcept;

    private:
        std::uint32_t m_side;
    };

}

#endif //MAD_SQUARE_HPP
