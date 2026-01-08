#include "ShapeRenderable.hpp"

namespace Graphics
{
    ShapeRenderable::ShapeRenderable(const Game::Entity& entity_)
        : Renderable(entity_)
    {};

    void ShapeRenderable::UpdatePosition()
    {
        const auto& entityPosition = entity.GetPosition();
        shape->setPosition(entityPosition.x, entityPosition.y);
    }
}
