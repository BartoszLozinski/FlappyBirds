#include "Text.hpp"

#include <filesystem>
#include <iostream>
#include <format>

namespace Graphics
{
    Text::Text(sf::RenderTarget& target_, const Utils::Vector2f& position, const unsigned size)
        : target(target_)
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
        target.draw(text);
    }

};
