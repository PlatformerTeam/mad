#include "DatabaseClientStorageDriver.hpp"


namespace mad::core {

    DatabaseClientStorageDriver::DatabaseClientStorageDriver(std::shared_ptr<Database> database) : m_database(std::move(database)) { }

    bool DatabaseClientStorageDriver::log_in(const std::string &username) const {
        if (m_database->is_user_exists(username)) {
            m_username = username;
            return true;
        }
        return false;
    }

    bool DatabaseClientStorageDriver::sign_up(const std::string &username) {
        if (!m_database->is_user_exists(username)) {
            m_database->registry_user(username);
            return true;
        }
        return false;
    }

    std::size_t DatabaseClientStorageDriver::get_progress() const {
        return m_database->get_progress(m_username);
    }

    void DatabaseClientStorageDriver::update_progress() {
        m_database->increment_progress(m_username);
    }

}
