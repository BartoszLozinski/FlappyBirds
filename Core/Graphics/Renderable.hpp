#pragma once

#include <SFML/Graphics.hpp>
#include <Game/Entity.hpp>

#include <memory>

class Renderable
{
protected:
    std::shared_ptr<Entity> entity = nullptr;

public:
    Renderable() = delete;
    Renderable(std::shared_ptr<Entity> entity_);
    virtual ~Renderable() = default;

    virtual void UpdatePosition() = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;
};
