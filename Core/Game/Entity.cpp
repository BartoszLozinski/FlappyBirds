#include "Entity.hpp"

Entity::Entity(const Vector2i& size_, const Vector2f& position_)
    : size(size_)
    , position(position_)
{};

Vector2i Entity::GetSize() const { return this->size; };
Vector2f Entity::GetPosition() const { return this->position; };
