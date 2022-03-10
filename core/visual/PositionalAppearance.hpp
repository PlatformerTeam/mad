#ifndef MAD_POSITIONALAPPEARANCE_HPP
#define MAD_POSITIONALAPPEARANCE_HPP

#include <common/FVec2D.hpp>
#include <event/VisualEvent.hpp>
#include <visual/image/Image.hpp>

#include <memory>


namespace mad::core {

    class PositionalAppearance : public VisualEvent {
    public:
        PositionalAppearance(std::shared_ptr<Vec2d> pos, std::shared_ptr<Image> img, int z_index);

    private:
        std::shared_ptr<Vec2d> m_position;
        std::shared_ptr<Image> m_image;
        int m_z_index;
    };

}// namespace mad::core

#endif//MAD_POSITIONALAPPEARANCE_HPP
