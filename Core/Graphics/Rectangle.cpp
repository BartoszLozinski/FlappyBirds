#include "Rectangle.hpp"

Rectangle::Rectangle(const Entity& entity_)
    : ShapeRenderable(entity_)
{
    Init();
};

void Rectangle::Init()
{
    const auto& entitySize = entity.GetSize();
    shape = std::make_unique<sf::RectangleShape>(sf::Vector2f{static_cast<float>(entitySize.x), static_cast<float>(entitySize.y)});
    shape->setOrigin(entitySize.x / 2, entitySize.y / 2);
    
    const auto& entityPosition = entity.GetPosition();
    shape->setPosition(entityPosition.x, entityPosition.y);
    shape->setFillColor(sf::Color::Green);
};

void Rectangle::Draw(sf::RenderWindow& window) const
{
    window.draw(*shape);
}
