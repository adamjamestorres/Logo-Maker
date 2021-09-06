//
// Created by Adam Torres on 5/30/21.
//

#include "TextCursor.h"

TextCursor::TextCursor()
        : deltaTime(0)
{
    if (!font.loadFromFile("../Fonts/calibri.ttf"))
    {
        std::cout << "Failed to load fonts correctly \n";
    }

    cursor.setFont(font);
    cursor.setString("|");
    cursor.setCharacterSize(20u);
    cursor.setFillColor(sf::Color::White);
}

void TextCursor::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    if(isEnabled)
        window.draw(cursor);
}

void TextCursor::update()
{
    deltaTime += clock.restart().asSeconds();

    if (deltaTime < 0.2f)
    {
        cursor.setFillColor(sf::Color::Transparent);
        return;
    }

    cursor.setFillColor(sf::Color::White);

    if (deltaTime >= 0.75f)
    {
        deltaTime = 0;
    }

}
