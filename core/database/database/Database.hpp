#ifndef MAD_DATABASE_HPP
#define MAD_DATABASE_HPP

#include <pqxx/pqxx>
#include <cstddef>


namespace mad::core {

    class Database {
    public:
        Database();

        bool is_user_exists(const std::string &username);

        void registry_user(const std::string &username);

        void append_level(const std::string &levelname);

        std::size_t get_id(const std::string &username);

        std::size_t get_progress(std::size_t id);
        std::size_t get_progress(const std::string &username);

        std::string get_levelname(std::size_t id);

        void increment_progress(std::size_t id);
        void increment_progress(const std::string &username);

        void reset_progress(std::size_t id);
        void reset_progress(const std::string &username);

    private:
        pqxx::connection m_connector;
        std::string m_query;

    };

}

#endif //MAD_DATABASE_HPP
