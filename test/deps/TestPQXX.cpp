#include <iostream>
#include <pqxx/pqxx>
#include <cstddef>


namespace mad::core {

    class Database {
    public:
        Database();

        bool is_user_exists(const std::string &username);

        void registry_user(const std::string &username);

        std::size_t get_id(const std::string &username);

        std::size_t get_progress(std::size_t id);
        std::size_t get_progress(const std::string &username);

        void increment_progress(std::size_t id);
        void increment_progress(const std::string &username);

        void reset_progress(std::size_t id);
        void reset_progress(const std::string &username);

    private:
        pqxx::connection m_connector;
        std::string m_query;

    };

}

namespace mad::core {

    Database::Database() : m_connector("dbname = mad") {
        try {
            if (m_connector.is_open()) {
                std::cout << "Database mad opened successfully" << '\n';
            } else {
                std::cout << "Can't open database mad" << '\n';
            }

            pqxx::work w(m_connector);

            m_query = "CREATE TABLE IF NOT EXISTS users("
                      "id SERIAL PRIMARY KEY,"
                      "name TEXT NOT NULL UNIQUE);";
            w.exec(m_query);

            m_query = "CREATE TABLE IF NOT EXISTS progress("
                      "id SERIAL PRIMARY KEY,"
                      "levels_completed SMALLINT NOT NULL);";
            w.exec(m_query);

            w.commit();

            std::cout << "Tables created successfully" << '\n';
        } catch (std::exception &exc) {
            std::cout << exc.what() << '\n';
        }
    }

    bool Database::is_user_exists(const std::string &username) {
        pqxx::work W(m_connector);
        m_query = "SELECT * FROM users WHERE name = '" + W.esc(username) + "';";
        pqxx::result rows_found = W.exec(m_query);
        return !rows_found.empty();
    }

    void Database::registry_user(const std::string &username) {
        pqxx::work W(m_connector);
        m_query = "INSERT INTO users(name) VALUES('" + W.esc(username) + "');";
        W.exec(m_query);
        m_query = "INSERT INTO progress(levels_completed) VALUES(0);";
        W.exec(m_query);
        W.commit();
    }

    std::size_t Database::get_id(const std::string &username) {
        pqxx::work W(m_connector);
        m_query = "SELECT * FROM users WHERE name = '" + W.esc(username) + "';";
        auto found_row = W.exec1(m_query);
        return found_row["id"].as<std::size_t>();
    }

    std::size_t Database::get_progress(std::size_t id) {
        pqxx::work W(m_connector);
        m_query = "SELECT * FROM progress WHERE id = " + std::to_string(id) + ";";
        auto found_row = W.exec1(m_query);
        return found_row["levels_completed"].as<std::size_t>();
    }

    std::size_t Database::get_progress(const std::string &username) {
        return get_progress(get_id(username));
    }

    void Database::increment_progress(std::size_t id) {
        pqxx::work W(m_connector);
        m_query = "UPDATE progress "
                  "SET levels_completed = levels_completed + 1 "
                  "WHERE id = " + std::to_string(id) + ";";
        W.exec(m_query);
        W.commit();
    }

    void Database::increment_progress(const std::string &username) {
        increment_progress(get_id(username));
    }

    void Database::reset_progress(std::size_t id) {
        pqxx::work W(m_connector);
        m_query = "UPDATE progress "
                  "SET levels_completed = 0 "
                  "WHERE id = " + std::to_string(id) + ";";
        W.exec(m_query);
        W.commit();
    }

    void Database::reset_progress(const std::string &username) {
        reset_progress(get_id(username));
    }
}

int main() {
    mad::core::Database db;

    db.registry_user("Denis");
    db.increment_progress("Denis");
    db.increment_progress("Denis");
    db.increment_progress("Denis");
    std::cout << db.get_progress("Denis") << '\n';
    db.reset_progress("Denis");
    std::cout << db.get_progress("Denis") << '\n';
}
