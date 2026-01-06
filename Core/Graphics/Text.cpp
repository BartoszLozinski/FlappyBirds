#include "Text.hpp"

namespace Graphics
{
    Text::Text(sf::RenderWindow& window_, const Utils::Vector2f& position, const unsigned size)
        : window(window_)
    {
        font.loadFromFile("../Core/Graphics/Arial.ttf");
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
