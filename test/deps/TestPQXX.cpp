#include <iostream>
#include <pqxx/pqxx>

class Database {
public:
    Database() : m_conn("dbname = mad") {
        try {
            if (m_conn.is_open()) std::cout << "Database opened successfully" << '\n';
            else std::cout << "Can't open database" << '\n';

            m_query = "CREATE TABLE IF NOT EXISTS users("
                      "id SERIAL PRIMARY KEY,"
                      "name TEXT NOT NULL);";

            pqxx::work W(m_conn);
            W.exec(m_query);
            W.commit();
            std::cout << "Table created successfully" << '\n';
        } catch (const std::exception &exc) {
            std::cout << exc.what() << '\n';
        }
    }

    bool log_in(const std::string &name) {
        pqxx::work W(m_conn);
        pqxx::result find_by_name = W.exec("SELECT * FROM users WHERE name = '" + W.esc(name) + "';");
        return !find_by_name.empty();
    }

    bool sign_up(const std::string &name) {
        try {
            pqxx::work W(m_conn);
            pqxx::result find_by_name = W.exec("SELECT * FROM users WHERE name = '" + W.esc(name) + "';");
            if (find_by_name.empty()) {
                m_query = "INSERT INTO users(name) VALUES('" + W.esc(name) + "');";
                W.exec(m_query);
                W.commit();
            } else {
                std::cout << "User already exists" << '\n';
            }
            return true;
        } catch (std::exception &exc) {
            std::cout << exc.what() << '\n';
            return false;
        }
    }

private:
    pqxx::connection m_conn;
    std::string m_query;
};

int main() {
    Database db;

    std::cout << db.sign_up("Denis") << '\n';
    std::cout << db.log_in("Denis") << '\n';
}
