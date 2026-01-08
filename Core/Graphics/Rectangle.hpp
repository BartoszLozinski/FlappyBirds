#pragma once

#include "ShapeRenderable.hpp"

namespace Graphics
{
    class Rectangle : public ShapeRenderable
    {
    protected:
        void Init() override final;
        

    public:
        Rectangle() = delete;
        ~Rectangle() = default;
        Rectangle(const Game::Entity& entity_);

        void Draw(sf::RenderWindow& window) const override;
    };
}
