#pragma once

#include <concepts>
#include <type_traits>

template<typename T>
concept TrivialType = std::is_trivial_v<T>;

template<TrivialType T>
struct Vector2x
{
    T x{};
    T y{};
};

using Vector2f = Vector2x<float>;
using Vector2i = Vector2x<int>;

class Entity
{
protected:
    Vector2i size{10, 10};
    Vector2f position{100.f, 100.f};

public:
    virtual ~Entity() = default;
    Entity(const Vector2i& size_, const Vector2f& position_);
    
    Vector2f GetPosition() const;
    Vector2i GetSize() const;
    //virtual void Control();
};
