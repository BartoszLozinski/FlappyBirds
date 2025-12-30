#include "ShapeRenderable.hpp"

ShapeRenderable::ShapeRenderable(const Entity& entity_)
    : Renderable(entity_)
{};

void ShapeRenderable::UpdatePosition()
{
    const auto& entityPosition = entity.GetPosition();
    shape->setPosition(entityPosition.x, entityPosition.y);
}
