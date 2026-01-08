#pragma once

#include "ShapeRenderable.hpp"

class Circle : public ShapeRenderable
{
protected:
    void Init() override final;
    
public:
    Circle() = delete;
    ~Circle() = default;
    Circle(const Game::Entity& entity_);

    void Draw(sf::RenderWindow& window) const override;
};
