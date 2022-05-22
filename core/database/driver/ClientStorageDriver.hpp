#ifndef MAD_CLIENTSTORAGEDRIVER_HPP
#define MAD_CLIENTSTORAGEDRIVER_HPP

#include <string>

#include <cstddef>


namespace mad::core {

    class ClientStorageDriver {
    public:
        virtual bool log_in(const std::string &username) const = 0;

        virtual bool sign_up(const std::string &username) = 0;

        virtual std::size_t get_progress(const std::string &username) const = 0;

        virtual void update_progress(const std::string &username) = 0;

        virtual ~ClientStorageDriver() = default;
    };

}

#endif //MAD_CLIENTSTORAGEDRIVER_HPP
