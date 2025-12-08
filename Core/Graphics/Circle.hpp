#pragma once

#include "ShapeRenderable.hpp"

class Circle : public ShapeRenderable
{
protected:


    void Init() override final;

public:
    Circle() = delete;
    ~Circle() = default;
    Circle(std::shared_ptr<Entity> entity_);

    void Draw(sf::RenderWindow& window) const override;
};
