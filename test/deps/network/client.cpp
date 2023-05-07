#include <httplib.h>
#include <iostream>

int main() {
    httplib::Client cli("localhost", 8080);

    auto res1 = cli.Post("/user/login", httplib::Params{
            {"username", "Denis"}
    });
    std::cout << res1->status << ' ' << res1->body << '\n';


    auto res2 = cli.Post("/user/login", httplib::Params{
            {"username", "NoDenis"}
    });
    std::cout << res2->status << ' ' << res2->body << '\n';

    auto res3 = cli.Post("/user/login", httplib::Params{
            {"name", "Denis"}
    });
    std::cout << res3->status << ' ' << res3->body << '\n';
}
