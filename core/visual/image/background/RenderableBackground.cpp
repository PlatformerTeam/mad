#include "RenderableBackground.hpp"

#include <utility>
#include <set>

namespace mad::core {


    RenderableBackground::RenderableBackground(const std::shared_ptr<BackgroundImage> &background,
                                               std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation) :
                                               m_camera_position(std::move(position)), m_rotation(std::move(rotation)),
                                               m_parallax_ratios(background->get_parallax_ratios()),
                                               m_last_camera_position(*m_camera_position) {
        is_active = background->is_active;

        std::set<std::string> sorted_files;

        for (const auto &file : std::filesystem::directory_iterator{background->get_path()}) {
            sorted_files.insert(file.path());
        }

        for (const auto &layer : sorted_files) {
            sf::Texture texture;
            CHECK_THROW(texture.loadFromFile(layer),
                        FileDoesNotExist, "Background file does not exist");
            texture.setRepeated(true);
            m_layers.push_back(texture);
        }
    }

    bool RenderableBackground::render(sf::RenderWindow &window) {
        for (int i = 0; i < static_cast<int>(m_layers.size()); i++) {
            sf::Sprite background;
            background.setTexture(m_layers[i]);
            float ratio = m_parallax_ratios[i];
            background.setScale(m_scale);
            if (m_layers_positions.size() == i) {
                m_layers_positions.push_back(*m_camera_position);
                background.setPosition(m_layers_positions[i]);
            } else {
                background.setPosition(m_layers_positions[i].get_x() + (*m_camera_position - m_last_camera_position).get_x() * ratio, m_camera_position->get_y());
            }
            m_layers_positions[i] += {(*m_camera_position - m_last_camera_position).get_x() * ratio, (*m_camera_position - m_layers_positions[i]).get_y()};
            background.setTextureRect({0, 0, static_cast<int>(window.getSize().x) * 3, static_cast<int>(window.getSize().y)});
            background.setOrigin(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 4); //static_cast<float>(window.getSize().y) / 2);
            window.draw(background);
        }
        m_last_camera_position = *m_camera_position;
        return true;
    }

    sf::RectangleShape RenderableBackground::get_physical_shape() noexcept {
        return sf::RectangleShape();
    }
}

