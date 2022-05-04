#ifndef MAD_CLIENTSTORAGEDRIVER_HPP
#define MAD_CLIENTSTORAGEDRIVER_HPP

#include <string>


namespace mad::core {

    class ClientStorageDriver {
    public:
        virtual bool log_in(std::string username) const = 0;

        virtual bool sign_up(std::string username) = 0;

        virtual std::size_t get_progress(std::string username) const = 0;

        virtual void update_progress(std::string username) = 0;

        virtual ~ClientStorageDriver() = default;
    };

}

#endif //MAD_CLIENTSTORAGEDRIVER_HPP
