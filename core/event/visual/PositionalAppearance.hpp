#ifndef MAD_POSITIONALAPPEARANCE_HPP
#define MAD_POSITIONALAPPEARANCE_HPP

#include "VisualEvent.hpp"
#include <common/FVec2D.hpp>
#include <visual/image/Image.hpp>

#include <memory>

namespace mad::core {

    struct PositionalAppearance : VisualEvent {
    public:
        [[nodiscard]] std::shared_ptr<Image> get_image() const noexcept;

        [[nodiscard]] std::shared_ptr<Vec2d> get_position() const noexcept;

        [[nodiscard]] int get_z_index() const noexcept;

    private:
        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<Image> m_image;

        [[maybe_unused]] int z_index;
    };

}

#endif //MAD_POSITIONALAPPEARANCE_HPP
