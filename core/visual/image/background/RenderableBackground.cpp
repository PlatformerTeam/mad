#include "RenderableBackground.hpp"

#include <utility>

namespace mad::core {


    RenderableBackground::RenderableBackground(const std::shared_ptr<BackgroundImage> &background,
                                               std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation) :
                                               m_position(std::move(position)), m_rotation(std::move(rotation)),
                                               m_parallax_ratio(background->get_parallax_ratio()) {
        is_active = background->is_active;

        CHECK_THROW(m_texture.loadFromFile(background->get_path()),
                    FileDoesNotExist, "Background file does not exist");

        m_texture.setRepeated(true);
    }

    bool RenderableBackground::render(sf::RenderWindow &window) {
        return false;
    }
}

