#include "ImageStorage.hpp"

#include <utility>

namespace mad::core {

    ImageStorage::ImageStorage(std::unordered_map<TypeAction, std::shared_ptr<Image>> actions)
                                : m_actions(std::move(actions)) {
    }

    std::shared_ptr<Image> ImageStorage::get_action(mad::core::ImageStorage::TypeAction type_action) noexcept {
        return m_actions[type_action];
    }

    std::unordered_map<ImageStorage::TypeAction, std::shared_ptr<Image>> ImageStorage::get_all_action() const noexcept {
        return m_actions;
    }

}
