#pragma once

#include <concepts>
#include <type_traits>

template<typename T>
concept TrivialType = std::is_trivial_v<T>;

template<TrivialType T>
struct Vector2x
{
    T x;
    T y;
};

using Vector2f = Vector2x<float>;
using Vector2i = Vector2x<int>;

class Entity
{
protected:
    Vector2i size{10, 10};

public:
    virtual ~Entity() = default;
    Vector2f position{100.f, 100.f};
    
    inline Vector2i GetSize() const { return this->size; } ;
    virtual void Control();
};
