#ifndef MAD_OFFLINECLIENTSTORAGEDRIVER_HPP
#define MAD_OFFLINECLIENTSTORAGEDRIVER_HPP

#include <database/driver/ClientStorageDriver.hpp>

#include <cstddef>


namespace mad::core {

    class OfflineClientStorageDriver : public ClientStorageDriver {
    public:
        explicit OfflineClientStorageDriver();

        bool log_in(std::string username) const override;

        bool sign_up(std::string username) override;

        std::size_t get_progress(std::string username) const override;

        void update_progress(std::string username) override;

    private:
        std::string m_username;
        std::size_t m_level_counter = 0;
    };

}

#endif //MAD_OFFLINECLIENTSTORAGEDRIVER_HPP
