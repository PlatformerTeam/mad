#include "OfflineClientStorageDriver.hpp"

#include <spdlog/spdlog.h>


namespace mad::core {

    OfflineClientStorageDriver::OfflineClientStorageDriver() = default;

    bool OfflineClientStorageDriver::log_in(const std::string &username) const {
        return m_username == username;
    }

    bool OfflineClientStorageDriver::sign_up(const std::string &username) {
        if (m_username.empty()) {
            m_username = username;
            return true;
        }
        return false;
    }

    std::size_t OfflineClientStorageDriver::get_progress(const std::string &username) const {
        return m_level_counter;
    }

    void OfflineClientStorageDriver::update_progress(const std::string &username) {
        m_level_counter++;
    }

}
