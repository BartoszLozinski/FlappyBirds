#include "Collision.hpp"

namespace Collision
{
    //Axis-Aligned Bounding Box for mid-point origins
    [[nodiscard]] bool AABB(const Entity& first, const Entity& second)
    {
        const auto firstPosition = first.GetPosition();
        const auto secondPosition = second.GetPosition();

        const auto firstSize = first.GetSize();
        const auto secondSize = second.GetSize();

        return std::abs(firstPosition.x - secondPosition.x) <= (firstSize.x * 0.5 + secondSize.x * 0.5) &&
               std::abs(firstPosition.y - secondPosition.y) <= (firstSize.y * 0.5 + secondSize.y * 0.5);
    }
}
