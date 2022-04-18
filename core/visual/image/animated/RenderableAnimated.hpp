#ifndef MAD_RENDERABLEANIMATED_HPP
#define MAD_RENDERABLEANIMATED_HPP


#include <visual/Renderable.hpp>
#include <visual/image/animated/AnimatedImage.hpp>
#include <common/FVec2D.hpp>
#include <common/Cast.hpp>
#include <common/Error.hpp>

namespace mad::core {

    class RenderableAnimated : public Renderable {
    public:
        explicit RenderableAnimated(const std::shared_ptr<AnimatedImage> &animated_image,
                                    std::shared_ptr<Vec2d> position, std::shared_ptr<float> rotation);

        void render(sf::RenderWindow &window) const override;

        int get_unique_number() const noexcept override;

        void update_frame() const;

    private:
        int32_t m_delta_time;

        sf::Texture m_texture;

        mutable sf::Clock m_clock;

        mutable sf::IntRect m_rect;

        std::shared_ptr<Vec2d> m_position;

        std::shared_ptr<float> m_rotation;

        int m_width_sprite;

        int m_height_sprite;

        int m_unique_number;
    };

}


#endif //MAD_RENDERABLEANIMATED_HPP
