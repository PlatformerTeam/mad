#include <Core.h>

#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Hello from example" << '\n';
    mad::core::Core obj;
    std::cout << obj.hello();
}
