#include <Game/Entity.hpp>

#include <iostream>
#include <format>


int main()
{
    Entity entity{{10, 20}, {200, 300}};

    std::cout << "Init program\n";
    std::cout << std::format("Entity position: ({}, {})\n", entity.GetPosition().x, entity.GetPosition().y); 
    std::cout << std::format("Entity size: ({}, {})\n", entity.GetSize().x, entity.GetSize().y);

    return 0;
};
