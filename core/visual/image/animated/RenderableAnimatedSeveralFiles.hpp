#ifndef MAD_RENDERABLEANIMATEDSEVERALFILES_HPP
#define MAD_RENDERABLEANIMATEDSEVERALFILES_HPP

#include <visual/Renderable.hpp>
#include <visual/image/animated/AnimatedImageSeveralFiles.hpp>
#include <common/FVec2D.hpp>
#include <common/Cast.hpp>
#include <common/Error.hpp>

#include <filesystem>

namespace mad::core {

    class RenderableAnimatedSeveralFiles : public Renderable {
    public:
        explicit RenderableAnimatedSeveralFiles(const std::shared_ptr<AnimatedImageSeveralFiles> &animated_image,
                                           std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation);

        bool render(sf::RenderWindow &window) override;

        void update_frame();

        sf::RectangleShape get_physical_shape() noexcept override;

    private:
        int32_t m_delta_time;

        std::vector<sf::Texture> m_textures;

        mutable sf::Clock m_clock;

        mutable Vec2d m_scale = {1, 1};

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

        size_t m_current_frame = 0;

        float m_delta_x;

        float m_delta_y;

        sf::RectangleShape m_physical_shape;

        int debug_prev_sprite_num = 0;

        std::vector<std::string> debug_m_textures_names;

        std::string debug_prev_name;
    };

}

#endif //MAD_RENDERABLEANIMATEDSEVERALFILES_HPP
