#include "PositionalAppearance.hpp"

#include <utility>


namespace mad::core {

    PositionalAppearance::PositionalAppearance(std::shared_ptr<Vec2d> pos, std::shared_ptr<float> rotation, std::shared_ptr<ImageStorage> image_storage, int z_index)
        : VisualEvent(VisualEvent::Kind::PositionalAppearance),
          m_position(std::move(pos)),
          m_rotation(std::move(rotation)),
          m_image_storage(std::move(image_storage)),
          m_z_index(z_index) {
    }

    std::shared_ptr<ImageStorage> PositionalAppearance::get_image_storage() const noexcept {
        return m_image_storage;
    }

    std::shared_ptr<Vec2d> PositionalAppearance::get_position() const noexcept {
        return m_position;
    }

    std::shared_ptr<float> PositionalAppearance::get_rotation() const noexcept {
        return m_rotation;
    }

    int PositionalAppearance::get_z_index() const noexcept {
        return m_z_index;
    }

}// namespace mad::core