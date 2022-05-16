#ifndef MAD_RENDERABLEANIMATEDONEFILE_HPP
#define MAD_RENDERABLEANIMATEDONEFILE_HPP


#include <visual/Renderable.hpp>
#include <visual/image/animated/AnimatedImageOneFile.hpp>
#include <common/FVec2D.hpp>
#include <common/Cast.hpp>
#include <common/Error.hpp>

namespace mad::core {

    class RenderableAnimatedOneFile : public Renderable {
    public:
        explicit RenderableAnimatedOneFile(const std::shared_ptr<AnimatedImageOneFile> &animated_image,
                                           std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation);

        bool render(sf::RenderWindow &window) override;

        void update_frame(bool &is_render_all) const;

    private:
        int32_t m_delta_time;

        sf::Texture m_texture;

        mutable sf::Clock m_clock;

        mutable sf::IntRect m_rect;

        mutable Vec2d m_scale = {1, 1};

        float m_width_scale;

        float m_height_scale;

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

        int m_width_sprite{};

        int m_height_sprite{};

    };

}

#endif //MAD_RENDERABLEANIMATEDONEFILE_HPP
