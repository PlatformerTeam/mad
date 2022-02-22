#include <Core.h>

#include <imgui.h>
#include <iostream>

int main() {
    std::cout << "Hello from example" << '\n';
    mad::core::Core obj;
    std::cout << obj.hello();
}
