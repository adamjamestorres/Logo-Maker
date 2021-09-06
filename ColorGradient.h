//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_COLORGRADIENT_H
#define FINAL_PROJECT_COLORGRADIENT_H
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "EventHandler.h"

class ColorGradient : public sf::Drawable
{
public:
    ColorGradient(float hue,sf::Vector2f pos);

    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    sf::FloatRect getGlobalBounds() { return backdrop.getGlobalBounds(); }
    sf::Color getChosenColor(sf::Vector2f mousePos);

private:
    std::array<int, 3> findRGB(float hue, float saturation, float value);

    float chosenHue;
    sf::Vector2f pos;
    sf::VertexArray vertexArray;
    sf::RectangleShape backdrop;
};


#endif //FINAL_PROJECT_COLORGRADIENT_H
