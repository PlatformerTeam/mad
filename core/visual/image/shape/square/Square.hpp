#ifndef MAD_SQUARE_HPP
#define MAD_SQUARE_HPP

#include "visual/image/shape/Shape.hpp"

namespace mad::core {

    class Square : public Shape {
    public:
        explicit Square(float side, Color color);

        [[nodiscard]] float get_side_length() const noexcept;

    private:
        float m_side;
    };

}

#endif //MAD_SQUARE_HPP
