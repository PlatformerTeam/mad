#ifndef MAD_IMAGESTORAGE_HPP
#define MAD_IMAGESTORAGE_HPP

#include <visual/image/Image.hpp>

#include <unordered_map>
#include <utility>

namespace mad::core {

    class ImageStorage {
    public:
        enum class TypeAction {
            Idle,
            Run,
            Attack_1_beg,
            Attack_1_end,
            Attack_2_beg,
            Attack_2_end,
            Attack_3_beg,
            Attack_3_end,
            Jump,
            Fly_up,
            Fall,
            Die,
            Hurt,
        };

        explicit ImageStorage(std::unordered_map<TypeAction, std::shared_ptr<Image>> actions);

        std::shared_ptr<Image> get_action(TypeAction type_action) noexcept;

        [[nodiscard]] std::unordered_map<TypeAction, std::shared_ptr<Image>> get_all_action() const noexcept;

    private:
        std::unordered_map<TypeAction, std::shared_ptr<Image>> m_actions;
    };

}

#endif //MAD_IMAGESTORAGE_HPP
