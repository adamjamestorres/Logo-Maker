//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_ITEM_H
#define FINAL_PROJECT_ITEM_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Item
{
public:
    Item(std::string str = "Default", unsigned int textSize = 20u, sf::Vector2f pos = { 0,0 });
    void setPosition(sf::Vector2f pos);
    void resize(unsigned int newSize);
    void setBoundarySize(sf::Vector2f size);
    void setColor(sf::Color color) { rect.setFillColor(color); }

public:
    sf::RectangleShape rect;
    sf::Text text;

private:
    void CenterText();
    sf::Font font;
};

#endif //FINAL_PROJECT_ITEM_H
