#include <Game/Bird.hpp>

#include <iostream>
#include <format>

int main()
{
    Bird bird{{10, 20}, {200, 300}};

    std::cout << "Init program\n";
    std::cout << std::format("Bird position: ({}, {})\n", bird.GetPosition().x, bird.GetPosition().y); 
    std::cout << std::format("Bird size: ({}, {})\n", bird.GetSize().x, bird.GetSize().y);

    return 0;
};
