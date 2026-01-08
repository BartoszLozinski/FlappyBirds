#pragma once

#include "Renderable.hpp"

class ShapeRenderable : public Renderable
{
protected:
    std::shared_ptr<sf::Shape> shape = nullptr;
    
    virtual void Init() = 0;

public:
    ShapeRenderable() = delete;
    ShapeRenderable(const Game::Entity& entity_);
    virtual ~ShapeRenderable() = default;

    virtual void UpdatePosition() override final;

};