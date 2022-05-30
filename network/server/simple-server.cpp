#include <database/database/Database.hpp>

#include <iostream>
#include <httplib.h>
#include <thread>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


int main() {
    httplib::Server svr;
    mad::core::Database db;

    svr.Get("/connection", [](const httplib::Request &req, httplib::Response &res) {
        res.status = 200;
        res.body = "Connected user port -- " + std::to_string(req.remote_port);
    });

    svr.Post("/user/login", [&db](const httplib::Request &req, httplib::Response &res) {
        if (req.has_param("username")) {
            auto username = req.get_param_value("username");
            if (db.is_user_exists(username)) {
                res.status = 200;
                res.body = "OK";
            } else {
                res.status = 404;
                res.body = "User doesn\'t exists";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    svr.Post("/user/signup", [&db](const httplib::Request &req, httplib::Response &res) {
        if (req.has_param("username")) {
            auto username = req.get_param_value("username");
            if (db.is_user_exists(username)) {
                res.status = 404;
                res.body = "User already exists";
            } else {
                db.registry_user(username);
                res.status = 200;
                res.body = "User doesn\'t exists";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    svr.Post("/user/progress", [&db](const httplib::Request &req, httplib::Response &res) {
        if (req.has_param("username")) {
            auto username = req.get_param_value("username");
            if (db.is_user_exists(username)) {
                res.status = 200;
                res.body = std::to_string(db.get_progress(username));
            } else {
                res.status = 404;
                res.body = "User doesn\'t exists";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    svr.Post("/user/increment-progress", [&db](const httplib::Request &req, httplib::Response &res) {
        if (req.has_param("username")) {
            auto username = req.get_param_value("username");
            if (db.is_user_exists(username)) {
                res.status = 200;
                res.body = "OK";
                db.increment_progress(username);
            } else {
                res.status = 404;
                res.body = "User doesn\'t exists";
            }
        } else {
            res.status = 404;
            res.body = "Invalid params of request";
        }
    });

    std::thread([&svr]() mutable {
        svr.listen("localhost", 8080);
    }).detach();

    sf::RenderWindow window(sf::VideoMode(640, 480), "MAD Server");
    ImGui::SFML::Init(window);
    window.setFramerateLimit(120);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
                svr.stop();
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        ImGui::Begin("Window");
        ImGui::Text("Hello");
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
