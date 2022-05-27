#ifndef MAD_DATABASECLIENTSTORAGEDRIVER_H
#define MAD_DATABASECLIENTSTORAGEDRIVER_H

#include <database/database/Database.hpp>
#include <database/driver/ClientStorageDriver.hpp>

#include <memory>


namespace mad::core {

    class DatabaseClientStorageDriver : public ClientStorageDriver {
    public:
        explicit DatabaseClientStorageDriver(std::shared_ptr<Database> database);

        bool log_in(const std::string &username) const override;

        bool sign_up(const std::string &username) override;

        std::size_t get_progress() const override;

        void update_progress() override;

    private:
        std::shared_ptr<Database> m_database;
        mutable std::string m_username;

    };

}


#endif//MAD_DATABASECLIENTSTORAGEDRIVER_H
