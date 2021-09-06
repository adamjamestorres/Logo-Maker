//
// Created by Adam Torres on 5/30/21.
//

#include "Button.h"

Button::Button()
{
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1.f);
    rect.setFillColor(sf::Color::Blue);
    rect.setSize({ 100.f,40.f });

    font.loadFromFile("../Fonts/OpenSans-Bold.ttf");
    text.setFont(font);
    text.setCharacterSize(15u);
    text.setFillColor(sf::Color::White);
}

void Button::setPosition(sf::Vector2f pos)
{
    rect.setPosition(pos);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(pos.x + rect.getGlobalBounds().width / 2, pos.y + rect.getGlobalBounds().height / 3);
}

void Button::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(rect);
    window.draw(text);
}
