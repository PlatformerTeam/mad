#include <Core.h>

#include <iostream>

int main() {
    std::cout << "Hello from example" << '\n';
    core::Core obj;
    std::cout << obj.hello();
}
