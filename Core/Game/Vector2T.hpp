#pragma once

#include <concepts>
#include <type_traits>

template<typename T>
concept TrivialType = std::is_trivial_v<T>;

template<TrivialType T>
struct Vector2t
{
    T x{};
    T y{};

    Vector2t& operator+=(const Vector2t& source)
    {
        this->x += source.x;
        this->y += source.y;
        return *this;
    }

    Vector2t& operator-=(const Vector2t& source)
    {
        this->x -= source.x;
        this->y -= source.y;
        return *this;
    }
};

using Vector2f = Vector2t<float>;
using Vector2u = Vector2t<unsigned>;
