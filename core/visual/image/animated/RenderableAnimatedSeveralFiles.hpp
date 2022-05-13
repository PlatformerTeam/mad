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

        void render(sf::RenderWindow &window) override;

        void update_frame();

    private:
        int32_t m_delta_time;

        std::vector<sf::Texture> m_textures;

        mutable sf::Clock m_clock;

        mutable Vec2d m_scale = {1, 1};

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

        size_t m_current_frame = 0;
    };

}

#endif //MAD_RENDERABLEANIMATEDSEVERALFILES_HPP
