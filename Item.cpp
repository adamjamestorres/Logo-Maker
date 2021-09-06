//
// Created by Adam Torres on 5/30/21.
//

#include "Item.h"

Item::Item(std::string str,unsigned int textSize, sf::Vector2f pos)
{
    if (!font.loadFromFile("../Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "Error, failed to load fonts in Item \n";
    }

    //Initialize Bounding box
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(2.0f);
    rect.setSize({float(textSize) * 10.f, float(textSize) + 10.f});
    rect.setOutlineColor(sf::Color::White);
    rect.setPosition(pos);

    //Initialize Text
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(textSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);

    //Centers Text on Local Object
    CenterText();

}

void Item::setPosition(sf::Vector2f pos)
{
    rect.setPosition(pos);
    CenterText();
}

void Item::resize(unsigned int newSize)
{
    rect.setSize({ float(newSize) * 10.f, float(newSize) + 10.f });
    text.setCharacterSize(newSize);

}

void Item::setBoundarySize(sf::Vector2f size)
{
    rect.setSize(size);
    CenterText();
}

void Item::CenterText()
{
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect rectBounds = rect.getGlobalBounds();

    text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
    text.setPosition(rectBounds.left + (rectBounds.width / 2.f),
                     rectBounds.top + (rectBounds.height / 3.f));
}