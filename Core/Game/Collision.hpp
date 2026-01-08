#pragma once

#include "Entity.hpp"

namespace Game::Collision
{
    //Axis-Aligned Bounding Box
    [[nodiscard]] bool AABB(const Entity& first, const Entity& second);

};
