//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_IMAGEPROPERTIES_H
#define FINAL_PROJECT_IMAGEPROPERTIES_H
#include <string>
#include <SFML/graphics.hpp>

struct ImageProperties
{
    float xPos;
    float yPos;
    float charSize;
    float rotation;

    std::string textString;

    sf::Color textColor;
    sf::Color backColor;
    sf::Font textFont;
};

#endif //FINAL_PROJECT_IMAGEPROPERTIES_H
