#include "PositionalAppearance.hpp"

namespace mad::core {

    std::shared_ptr<Image> PositionalAppearance::get_image() const noexcept {
        return m_image;
    }

    std::shared_ptr<Vec2d> PositionalAppearance::get_position() const noexcept {
        return m_position;
    }

    int PositionalAppearance::get_z_index() const noexcept {
        return z_index;
    }

}

