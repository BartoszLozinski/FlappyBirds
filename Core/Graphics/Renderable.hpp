#pragma once

#include <SFML/Graphics.hpp>
#include <Game/Entity.hpp>

#include <memory>

class Renderable
{
protected:
    const Game::Entity& entity;

public:
    Renderable() = delete;
    Renderable(const Game::Entity& entity_);
    virtual ~Renderable() = default;

    virtual void UpdatePosition() = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;
};
