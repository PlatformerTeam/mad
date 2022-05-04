#include "OfflineClientStorageDriver.hpp"


namespace mad::core {

    OfflineClientStorageDriver::OfflineClientStorageDriver() = default;

    bool OfflineClientStorageDriver::log_in(std::string username) const {
        return m_username == username;
    }

    bool OfflineClientStorageDriver::sign_up(std::string username) {
        if (m_username == "") {
            m_username = std::move(username);
            return true;
        }
        return false;
    }

    std::size_t OfflineClientStorageDriver::get_progress(std::string username) const {
        return m_level_counter;
    }

    void OfflineClientStorageDriver::update_progress(std::string username) {
        m_level_counter++;
    }

}
