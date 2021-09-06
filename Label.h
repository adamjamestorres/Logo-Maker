//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_LABEL_H
#define FINAL_PROJECT_LABEL_H
#include <SFML/Graphics.hpp>

class Label : public sf::Text
{
public:
    Label()
    {
        font.loadFromFile("../Fonts/OpenSans-Bold.ttf");
        this->setFont(font);
        this->setCharacterSize(15u);
        this->setFillColor(sf::Color::White);
    }
private:
    sf::Font font;
};

#endif //FINAL_PROJECT_LABEL_H
