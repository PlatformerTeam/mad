#include <database/driver/ClientStorageDriver.hpp>
#include <event/management/dispatcher/EventDispatcher.hpp>
#include <event/management/handler/AuthorizationMenuEventsHandler.hpp>
#include <event/management/handler/MainMenuEventsHandler.hpp>
#include <event/management/handler/WindowCloseHandler.hpp>
#include <event/management/handler/GameRunnerEventsHandler.hpp>
#include <event/management/producer/SystemListener.hpp>
#include <loader/LevelLoader.hpp>
#include <menu/AuthorizationMenu.hpp>
#include <menu/MainMenu.hpp>
#include <runner/GameRunner.hpp>
#include <world/LocalWorld.hpp>
#include <loader/LevelLoaderFromServer.hpp>

#include <httplib.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <spdlog/spdlog.h>

namespace mad::core {

    class NetworkClientStorageDriver : public ClientStorageDriver {
    public:
        explicit NetworkClientStorageDriver() : m_client("localhost", 8080) {
            auto res = m_client.Get("/connection");
            SPDLOG_DEBUG("Connection request result:\n\tStatus: " + std::to_string(res->status) + "\n\tMessage: " + res->body);
        }

        bool log_in(const std::string &username) const override {
            auto res = m_client.Post("/user/login", httplib::Params{
                    {"username", username}
            });
            SPDLOG_DEBUG("Login request result:\n\tStatus: " + std::to_string(res->status) + "\n\tMessage: " + res->body);
            if (res->status == 200) {
                m_username = username;
            }
            return res->status == 200;
        }

        bool sign_up(const std::string &username) override {
            auto res = m_client.Post("/user/signup", httplib::Params{
                    {"username", username}
            });
            SPDLOG_DEBUG("Sign up request result:\n\tStatus: " + std::to_string(res->status) + "\n\tMessage: " + res->body);
            return res->status == 200;
        }

        std::size_t get_progress() const override {
            auto res = m_client.Post("/user/progress", httplib::Params{
                    {"username", m_username}
            });
            SPDLOG_DEBUG("Get progress request result:\n\tStatus: " + std::to_string(res->status) + "\n\tMessage: " + res->body);
            return std::stoi(res->body);
        }

        void update_progress() override {
            auto res = m_client.Post("/user/increment-progress", httplib::Params{
                    {"username", m_username}
            });
            SPDLOG_DEBUG("Update request result:\n\tStatus: " + std::to_string(res->status) + "\n\tMessage: " + res->body);
        }

        std::vector<std::shared_ptr<LevelLoader>> get_levels() {
            auto res = m_client.Get("/level/total");
            std::size_t level_count = std::stoi(res->body);
            std::vector<std::shared_ptr<LevelLoader>> loaders;
            for (std::size_t i = 1; i <= level_count; ++i) {
                auto res1 = m_client.Post("/level/load", httplib::Params{
                        {"number", std::to_string(i)}
                });
                json config;
                std::stringstream ss;
                ss << res1->body;
                ss >> config;
                loaders.push_back(std::make_shared<LevelLoaderFromServer>(config["map"], config));
            }
            return loaders;
        }

    private:
        mutable std::string m_username;
        mutable httplib::Client m_client;

    };

}

int main() {
#ifndef NDEBUG
    auto log_level = spdlog::level::trace;
#else
    auto log_level = spdlog::level::info;
#endif
    spdlog::set_level(log_level);

    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "MAD");
    ImGui::SFML::Init(*window);
    window->setFramerateLimit(120);

    auto global_dispatcher = std::make_shared<mad::core::ImmediateDispatcher>();

    auto system_listener = std::make_shared<mad::core::SystemListener>(window);

    auto network_storage_driver = std::make_shared<mad::core::NetworkClientStorageDriver>();

    std::vector<std::shared_ptr<mad::core::LevelLoader>> level_loaders = network_storage_driver->get_levels();

    auto game_runner = std::make_unique<mad::core::GameRunner>(
            level_loaders,
            global_dispatcher,
            std::make_unique<mad::core::MainMenu>(),
            std::make_unique<mad::core::AuthorizationMenu>(network_storage_driver),
            system_listener,
            network_storage_driver
    );

    global_dispatcher->registry(std::make_shared<mad::core::WindowCloseHandler>(*window));
    global_dispatcher->registry(std::make_shared<mad::core::MainMenuEventsHandler>(*game_runner));
    global_dispatcher->registry(std::make_shared<mad::core::GameRunnerEventsHandler>(*game_runner, network_storage_driver));
    global_dispatcher->registry(std::make_shared<mad::core::AuthorizationMenuEventsHandler>(*game_runner));

    game_runner->run(*window);

    ImGui::SFML::Shutdown();
}
