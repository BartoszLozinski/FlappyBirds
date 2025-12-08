#include "ShapeRenderable.hpp"

ShapeRenderable::ShapeRenderable(std::shared_ptr<Entity> entity_)
    : Renderable(entity_)
{};

void ShapeRenderable::UpdatePosition()
{
    const auto& entityPosition = entity->GetPosition();
    shape->setPosition(entityPosition.x, entityPosition.y);
}
