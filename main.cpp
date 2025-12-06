#include <Game/Entity.hpp>

#include <iostream>
#include <format>


int main()
{
    Entity entity;

    std::cout << "Init program\n";
    std::cout << std::format("Entity position: ({}, {})\n", entity.position.x, entity.position.y); 
    std::cout << std::format("Entity size: ({}, {})\n", entity.GetSize().x, entity.GetSize().y);

    return 0;
};
