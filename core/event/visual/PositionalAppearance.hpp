#ifndef MAD_POSITIONALAPPEARANCE_HPP
#define MAD_POSITIONALAPPEARANCE_HPP

#include <common/FVec2D.hpp>
#include <event/visual/VisualEvent.hpp>
#include <visual/image/Image.hpp>
#include <visual/image/storage/ImageStorage.hpp>
#include <world/entity/Entity.hpp>

#include <memory>


namespace mad::core {

    class PositionalAppearance : public VisualEvent {
    public:
        PositionalAppearance(std::shared_ptr<Vec2d> pos, std::shared_ptr<float> rotation,
                             std::shared_ptr<ImageStorage> image_storage, int z_index,
                             Entity::Id entity_id);

        [[nodiscard]] std::shared_ptr<ImageStorage> get_image_storage() const noexcept;

        [[nodiscard]] std::shared_ptr<Vec2d> get_position() const noexcept;
        [[nodiscard]] std::shared_ptr<float> get_rotation() const noexcept;

        [[nodiscard]] int get_z_index() const noexcept;

        [[nodiscard]] Entity::Id get_entity_id() const noexcept;

    private:
        std::shared_ptr<Vec2d> m_position;
        std::shared_ptr<float> m_rotation;
        std::shared_ptr<ImageStorage> m_image_storage;
        Entity::Id m_entity_id;
        int m_z_index;
    };

}// namespace mad::core

#endif//MAD_POSITIONALAPPEARANCE_HPP
