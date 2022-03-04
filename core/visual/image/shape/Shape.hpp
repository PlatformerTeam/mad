#ifndef MAD_CORE_VISUAL_IMAGE_SHAPE_HPP
#define MAD_CORE_VISUAL_IMAGE_SHAPE_HPP

#include <visual/image/Image.hpp>


namespace mad::core {

    class Shape : public Image {
    public:
        enum class Geometry {
            Square
        };

        [[nodiscard]] Geometry get_geometry() const noexcept;

    private:
        const Geometry m_geometry;
    };

}


#endif //MAD_CORE_VISUAL_IMAGE_SHAPE_HPP
