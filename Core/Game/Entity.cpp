#include "Entity.hpp"

namespace Game
{
    Entity::Entity(const Utils::Vector2u& size_, const Utils::Vector2f& position_)
        : size(size_)
        , position(position_)
    {};

    Utils::Vector2u Entity::GetSize() const { return this->size; };
    Utils::Vector2f Entity::GetPosition() const { return this->position; };

    void Entity::Kill()
    {
        isAlive = false;
    }

    bool Entity::IsAlive() const
    {
        return isAlive;
    }
}