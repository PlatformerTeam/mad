#include "PositionalAppearance.hpp"

#include <utility>


namespace mad::core {

    PositionalAppearance::PositionalAppearance(std::shared_ptr<Vec2d> pos, std::shared_ptr<Image> img, int z_index) : m_position(std::move(pos)), m_image(std::move(img)), m_z_index(z_index) {}

}// namespace mad::core
