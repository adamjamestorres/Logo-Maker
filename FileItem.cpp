//
// Created by Adam Torres on 5/30/21.
//

#include "FileItem.h"

FileItem::FileItem(ImageEnum image, std::string text, unsigned int size, sf::Vector2f position)
        : Item(text, size, position), icon(image,size)
{
    SetItemPreferences(); //Sets rect and text preferences
}

void FileItem::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    //Draws rect, text and icon to screen
    window.draw(rect);
    window.draw(text);
    window.draw(icon);
}

void FileItem::setPosition(sf::Vector2f pos)
{
    Item::setPosition(pos);
    icon.setPosition(pos);
    LeftAlignText();
}

void FileItem::SetItemPreferences()
{
    //Sets basic background parameters for this directory use case
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Transparent);
    rect.setOutlineThickness(0);
}

void FileItem::LeftAlignText()
{
    //Aligns text to the left right behind the icon following a move of the item bounding box rect

    sf::FloatRect iconBounds = icon.getGlobalBounds();
    float padding = 5.f;

    text.setOrigin(0.f, 0.f);
    text.setPosition(rect.getPosition().x + iconBounds.width + padding, rect.getPosition().y);
}