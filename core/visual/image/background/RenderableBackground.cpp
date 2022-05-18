#include "RenderableBackground.hpp"

#include <utility>
#include <set>

namespace mad::core {


    RenderableBackground::RenderableBackground(const std::shared_ptr<BackgroundImage> &background,
                                               std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation) :
                                               m_position(std::move(position)), m_rotation(std::move(rotation)),
                                               m_parallax_ratios(background->get_parallax_ratios()) {
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
        for (const auto &current_layer : m_layers) {
            sf::Sprite background;
            background.setTexture(current_layer);
            background.setPosition(*m_position);
            background.setScale({0.5, 0.5});
            background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
            window.draw(background);
        }
        return true;
    }

    sf::RectangleShape RenderableBackground::get_physical_shape() noexcept {
        return sf::RectangleShape();
    }
}

