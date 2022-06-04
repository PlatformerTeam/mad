#include <database/database/Database.hpp>

#include <httplib.h>
#include <thread>
#include <vector>
#include <mutex>
#include <filesystem>
#include <fstream>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


int main() {
    httplib::Server svr;
    mad::core::Database db;
    std::filesystem::path levels_directory = "../../resources/levels";

    std::mutex locker;
    std::vector<std::string> logs;

    svr.Get("/connection", [&logs, &locker](const httplib::Request &req, httplib::Response &res) {
        std::unique_lock lock(locker);
        res.status = 200;
        res.body = "Connection successful";
        logs.push_back("Connected user port " + std::to_string(req.remote_port));
    });

    svr.Get("/level/total", [&logs, &locker, &db](const httplib::Request &req, httplib::Response &res) {
        std::unique_lock lock(locker);
        res.status = 200;
        res.body = std::to_string(db.get_levels_total());
        logs.push_back("Send total level counter to port " + std::to_string(req.remote_port));
    });

    svr.Post("/level/load", [&logs, &locker, &db, &levels_directory](const httplib::Request &req, httplib::Response &res) {
        std::unique_lock lock(locker);
        if (req.has_param("number")) {
            auto number = std::stoi(req.get_param_value("number"));
            if (number <= db.get_levels_total()) {
                auto levelname = db.get_levelname(number);
                auto cur_level_directory = levels_directory / levelname;
                std::ifstream input_config(cur_level_directory / "config.json");
                std::ifstream input_map(cur_level_directory / "map");
                json config;
                std::string map, map_line;
                input_config >> config;
                while (input_map >> map_line) {
                    map += map_line;
                }
                config["map"] = map;
                res.status = 200;
                res.body = to_string(config);
                logs.push_back("Send level " + levelname + " to port " + std::to_string(req.remote_port));
            } else {
                res.status = 404;
                res.body = "Invalid number of level";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    svr.Post("/user/login", [&db, &logs, &locker](const httplib::Request &req, httplib::Response &res) {
        std::unique_lock lock(locker);
        if (req.has_param("username")) {
            auto username = req.get_param_value("username");
            if (db.is_user_exists(username)) {
                res.status = 200;
                res.body = "OK";
                logs.push_back("User " + std::to_string(req.remote_port) + " login as " + username);
            } else {
                res.status = 404;
                res.body = "User doesn\'t exists";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    svr.Post("/user/signup", [&db, &logs, &locker](const httplib::Request &req, httplib::Response &res) {
        std::unique_lock lock(locker);
        if (req.has_param("username")) {
            auto username = req.get_param_value("username");
            if (db.is_user_exists(username)) {
                res.status = 404;
                res.body = "User already exists";
                logs.push_back("Register new user " + username + " from port " + std::to_string(req.remote_port));
            } else {
                db.registry_user(username);
                res.status = 200;
                res.body = "User " + username + " is registered";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    svr.Post("/user/progress", [&db, &logs, &locker](const httplib::Request &req, httplib::Response &res) {
        std::unique_lock lock(locker);
        if (req.has_param("username")) {
            auto username = req.get_param_value("username");
            if (db.is_user_exists(username)) {
                res.status = 200;
                res.body = std::to_string(db.get_progress(username));
                logs.push_back("Send progress to user " + username);
            } else {
                res.status = 404;
                res.body = "User doesn\'t exists";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    svr.Post("/user/increment-progress", [&db, &logs, &locker](const httplib::Request &req, httplib::Response &res) {
        std::unique_lock lock(locker);
        if (req.has_param("username")) {
            auto username = req.get_param_value("username");
            if (db.is_user_exists(username)) {
                res.status = 200;
                res.body = "OK";
                db.increment_progress(username);
                logs.push_back("Increment progress for user " + username);
            } else {
                res.status = 404;
                res.body = "User doesn\'t exists";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    sf::RenderWindow window(sf::VideoMode(640, 480), "MAD Server");
    ImGui::SFML::Init(window);
    window.setFramerateLimit(120);
    char input_levelname[255] = "\0";
    std::string text_hint = "new level name";
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
                if (svr.is_running()) {
                    svr.stop();
                }
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        ImGui::SetNextWindowSize(ImVec2(window.getSize().x, window.getSize().y));
        ImGui::SetNextWindowPos({0, 0});
        ImGui::Begin("Server util", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        {
            std::unique_lock lock(locker);
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
            ImGui::BeginChild("Tool buttons", ImVec2(ImGui::GetContentRegionAvail().x * 0.3f, 82), true, window_flags);
            if (ImGui::Button("Start server")) {
                if (!svr.is_running()) {
                    std::thread([&svr]() mutable {
                        svr.listen("localhost", 8080);
                    }).detach();
                    logs.emplace_back("Server has started");
                }
            }

            if (ImGui::Button("Stop server")) {
                if (svr.is_running()) {
                    svr.stop();
                    logs.emplace_back("Server has stopped");
                }
            }

            if (ImGui::Button("Quit")) {
                window.close();
                if (svr.is_running()) {
                    svr.stop();
                }
            }
            ImGui::EndChild();
        }

        ImGui::SameLine();
        {
            std::unique_lock lock(locker);
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
            ImGui::BeginChild("Input levelname", ImVec2(ImGui::GetContentRegionAvail().x, 82), true, window_flags);
            ImGui::InputText("##", input_levelname, 255);
            ImGui::Text(text_hint.c_str());
            if (ImGui::Button("Enter")) {
                if (!std::string(input_levelname).empty()) {
                    std::filesystem::path level_container = levels_directory / input_levelname;
                    if (std::filesystem::is_directory(level_container) &&
                            std::filesystem::exists(level_container / "config.json") &&
                            std::filesystem::exists(level_container / "map")) {
                        if (!db.is_level_exists(input_levelname)) {
                            db.append_level(input_levelname);
                            text_hint = "new level name";
                        } else {
                            text_hint = "level name is already used";
                        }
                    } else {
                        text_hint = "wrong directory format";
                    }
                } else {
                    text_hint = "string is empty";
                }
            }
            ImGui::EndChild();
        }

        {
            std::unique_lock lock(locker);
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
            ImGui::BeginChild("Logs", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true, window_flags);
            for (int i = 0; i < logs.size(); ++i) {
                ImGui::Text(logs[i].c_str(), i);
            }
            ImGui::EndChild();
        }

        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
