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
            Attack
        };

        std::shared_ptr<Image> get_action(TypeAction type_action);

    private:
        std::unordered_map<TypeAction, std::shared_ptr<Image>> m_actions;
    };

}

#endif //MAD_IMAGESTORAGE_HPP
