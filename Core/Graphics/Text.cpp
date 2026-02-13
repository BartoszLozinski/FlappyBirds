#include "Text.hpp"

#include <filesystem>
#include <iostream>
#include <format>

namespace Graphics
{
    Text::Text(sf::RenderWindow& window_, const Utils::Vector2f& position, const unsigned size)
        : window(window_)
    {
        std::filesystem::path fontPath = std::filesystem::current_path();
        fontPath /= "../Core/Graphics/Arial.ttf";
        font.loadFromFile(fontPath);
        text.setFont(font);
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(size);
        text.setPosition(position.x, position.y);
        text.setStyle(sf::Text::Bold);
    }

    void Text::DisplayText(const std::string& textString)
    {
        text.setString(textString);
        window.draw(text);
    }

};
