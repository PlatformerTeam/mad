#ifndef MAD_CORE_VISUAL_IMAGE_SHAPE_HPP
#define MAD_CORE_VISUAL_IMAGE_SHAPE_HPP

#include <visual/image/Image.hpp>
#include <common/Color.hpp>


namespace mad::core {

    class Shape : public Image {
    public:
        enum class Geometry {
            Square
        };

        [[nodiscard]] Geometry get_geometry() const noexcept;

    protected:
        const Geometry m_geometry;
        Color m_color;
    };

}


#endif //MAD_CORE_VISUAL_IMAGE_SHAPE_HPP
