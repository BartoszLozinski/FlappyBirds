#pragma once

#include <random>
#include <concepts>
#include <type_traits>

namespace Utils
{
    template<typename T>
    concept TrivialType = std::is_trivial_v<T>;

    template<TrivialType T>
    class RandomGenerator
    {
    private:
        T min{};
        T max{};
  
        std::mt19937 engine{std::random_device{}()};
    public:

        RandomGenerator(const T min_, const T max_)
            : min(min_)
            , max(max_)
            {};

        
        T Generate()
        {
            std::uniform_real_distribution<T> distribution{min, max};
            return distribution(engine);
        }
    };

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

}


