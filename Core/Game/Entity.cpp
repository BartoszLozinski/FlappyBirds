#include "Entity.hpp"

Entity::Entity(const Vector2u& size_, const Vector2f& position_)
    : size(size_)
    , position(position_)
{};

Vector2u Entity::GetSize() const { return this->size; };
Vector2f Entity::GetPosition() const { return this->position; };
