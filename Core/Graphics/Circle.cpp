#include "Circle.hpp"

Circle::Circle(std::shared_ptr<Entity> entity_)
    : ShapeRenderable(entity_)
{
    Init();
};

void Circle::Init()
{
    const auto& entitySize = entity->GetSize();
    shape = std::make_unique<sf::CircleShape>(entitySize.x);
    shape->setOrigin(entitySize.x / 2, entitySize.y / 2);
    const auto& entityPosition = entity->GetPosition();
    shape->setPosition(entityPosition.x, entityPosition.y);
    shape->setFillColor(sf::Color::Magenta);
};

void Circle::Draw(sf::RenderWindow& window) const
{
    window.draw(*shape);
}
