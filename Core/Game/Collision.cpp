#include "Collision.hpp"

namespace Collision
{
    //Axis-Aligned Bounding Box
    [[nodiscard]] bool AABB(const Entity& first, const Entity& second)
    {
        const auto firstPosition = first.GetPosition();
        const auto secondPosition = second.GetPosition();

        const auto firstSize = first.GetSize();
        const auto secondSize = second.GetSize();

        return std::abs(firstPosition.x - secondPosition.x) <= (firstSize.x + secondSize.x) &&
               std::abs(firstPosition.y - secondPosition.y) <= (firstSize.y + secondSize.y);
    }
}
