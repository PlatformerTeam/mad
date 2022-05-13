#include "ImageStorage.hpp"

namespace mad::core {

    std::shared_ptr<Image> ImageStorage::get_action(mad::core::ImageStorage::TypeAction type_action) {
        return m_actions[type_action];
    }

}
