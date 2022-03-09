#ifndef MAD_POSITIONALAPPEARANCE_HPP
#define MAD_POSITIONALAPPEARANCE_HPP

#include <event/VisualEvent.hpp>
#include <visual/image/Image.hpp>
#include <common/FVec2D.hpp>

#include <memory>


namespace mad::core {

    class PositionalAppearance : public VisualEvent {
        std::unique_ptr<Vec2d> position;
        std::shared_ptr<Vec2d> image;
        int z_index;
    };

}

#endif //MAD_POSITIONALAPPEARANCE_HPP
