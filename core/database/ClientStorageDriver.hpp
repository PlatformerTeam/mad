#ifndef MAD_CLIENTSTORAGEDRIVER_HPP
#define MAD_CLIENTSTORAGEDRIVER_HPP

#include <string>


namespace mad::core {

    class ClientStorageDriver {
    public:
        virtual bool log_in(std::string username) = 0;

        virtual bool sign_up(std::string username) = 0;

        virtual ~ClientStorageDriver() = default;
    };

}

#endif //MAD_CLIENTSTORAGEDRIVER_HPP
