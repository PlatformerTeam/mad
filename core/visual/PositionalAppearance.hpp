#ifndef MAD_POSITIONALAPPEARANCE_HPP
#define MAD_POSITIONALAPPEARANCE_HPP

#include <event/VisualEvent.hpp>

#include <memory>


// Forward declarations
namespace mad::core {
    class Vec2d;
    class Image;
}

namespace mad::core {

    class PositionalAppearance : public VisualEvent {
    private:
        std::unique_ptr<Vec2d> m_position;
        std::shared_ptr<Image> m_image;
        int m_z_index;
    };

}

#endif //MAD_POSITIONALAPPEARANCE_HPP
