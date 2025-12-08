#pragma once

#include "Renderable.hpp"

class ShapeRenderable : public Renderable
{
protected:
    std::unique_ptr<sf::Shape> shape = nullptr;
    
    virtual void Init() = 0;

public:
    ShapeRenderable() = delete;
    ShapeRenderable(std::shared_ptr<Entity> entity_);
    virtual ~ShapeRenderable() = default;

    virtual void UpdatePosition() override;

};