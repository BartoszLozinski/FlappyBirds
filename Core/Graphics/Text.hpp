#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window.hpp>

#include "Utils/Utils.hpp"

namespace Graphics
{
    class Text
    {
    private:
        sf::Font font{};
        sf::Text text{};
        sf::RenderWindow& window;

    public:
        Text(sf::RenderWindow& window_ , const Utils::Vector2f& position = {0.0f, 0.0f}, const unsigned size = 24);
        Text(const Text&) = delete;
        Text(Text&&) = delete;
        Text& operator=(const Text&) = delete;
        Text& operator=(Text&&) = delete;

        void DisplayText(const std::string& textString);

    };
};
