#include <database/database/Database.hpp>

#include <iostream>
#include <httplib.h>

int main() {
    httplib::Server svr;
    mad::core::Database db;

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

    svr.listen("localhost", 8080);
}
